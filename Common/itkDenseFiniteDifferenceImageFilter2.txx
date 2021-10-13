/*=========================================================================

  Program:   Tensor ToolKit - TTK
  Module:    $URL$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) INRIA 2010. All rights reserved.
  See LICENSE.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkDenseFiniteDifferenceImageFilter2.txx,v $
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkDenseFiniteDifferenceImageFilter2_txx_
#define __itkDenseFiniteDifferenceImageFilter2_txx_
#include "itkDenseFiniteDifferenceImageFilter2.h"

#include <list>
#include "itkImageRegionConstIterator.h"
#include "itkImageRegionIterator.h"
#include "itkNumericTraits.h"

namespace itk {

template <class TInputImage, class TOutputImage>
void
DenseFiniteDifferenceImageFilter2<TInputImage, TOutputImage>
::CopyInputToOutput()
{
  typename TInputImage::ConstPointer  input  = this->GetInput();
  typename TOutputImage::Pointer      output = this->GetOutput();

  if ( !input || !output )
    {
    itkExceptionMacro(<< "Either input and/or output is NULL.");
    }

  // Check if we are doing in-place filtering
  if ( this->GetInPlace() && (typeid(TInputImage) == typeid(TOutputImage)) )
    {
    typename TInputImage::Pointer tempPtr = 
      dynamic_cast<TInputImage *>( output.GetPointer() );
    if ( tempPtr && tempPtr->GetPixelContainer() == input->GetPixelContainer() )
      {
      // the input and output container are the same - no need to copy
      return;
      }
    }
  
  ImageRegionConstIterator<TInputImage>  in(input, output->GetRequestedRegion());
  ImageRegionIterator<TOutputImage> out(output, output->GetRequestedRegion());

  while( ! out.IsAtEnd() )
    {
    out.Value() =  in.Get();  // Supports input image adaptors only
    ++in;
    ++out;
    }
}

template <class TInputImage, class TOutputImage>
void
DenseFiniteDifferenceImageFilter2<TInputImage, TOutputImage>
::AllocateUpdateBuffer()
{
  // The update buffer looks just like the output.
  typename TOutputImage::Pointer output = this->GetOutput();

  m_UpdateBuffer->SetLargestPossibleRegion(output->GetLargestPossibleRegion());
  m_UpdateBuffer->SetRequestedRegion(output->GetRequestedRegion());
  m_UpdateBuffer->SetBufferedRegion(output->GetBufferedRegion());
  m_UpdateBuffer->Allocate();
}

template<class TInputImage, class TOutputImage>
void
DenseFiniteDifferenceImageFilter2<TInputImage, TOutputImage>
::ApplyUpdate(const TimeStepType &dt)
{
  // Set up for multithreaded processing.
  DenseFDThreadStruct str;
  str.Filter = this;
  str.TimeStep = dt;
  this->GetMultiThreader()->SetNumberOfWorkUnits(this->GetNumberOfWorkUnits());
  this->GetMultiThreader()->SetSingleMethod(this->ApplyUpdateThreaderCallback,
                                            &str);
  // Multithread the execution
  this->GetMultiThreader()->SingleMethodExecute();
}

template<class TInputImage, class TOutputImage>
ITK_THREAD_RETURN_FUNCTION_CALL_CONVENTION
DenseFiniteDifferenceImageFilter2<TInputImage, TOutputImage>
::ApplyUpdateThreaderCallback( void * arg )
{
  DenseFDThreadStruct * str;
  int total, threadId, threadCount;

  threadId = ((MultiThreaderBase::WorkUnitInfo *)(arg))->WorkUnitID;
  threadCount = ((MultiThreaderBase::WorkUnitInfo *)(arg))->NumberOfWorkUnits;

  str = (DenseFDThreadStruct *)(((MultiThreaderBase::WorkUnitInfo *)(arg))->UserData);

  // Execute the actual method with appropriate output region
  // first find out how many pieces extent can be split into.
  // Using the SplitRequestedRegion method from itk::ImageSource.
  ThreadRegionType splitRegion;
  total = str->Filter->SplitRequestedRegion(threadId, threadCount,
                                            splitRegion);
  
  if (threadId < total)
    {
    str->Filter->ThreadedApplyUpdate(str->TimeStep, splitRegion, threadId);
    }

  return ITK_THREAD_RETURN_DEFAULT_VALUE;
}

template <class TInputImage, class TOutputImage>
typename
DenseFiniteDifferenceImageFilter2<TInputImage, TOutputImage>::TimeStepType
DenseFiniteDifferenceImageFilter2<TInputImage, TOutputImage>
::CalculateChange()
{
  int threadCount;
  TimeStepType dt;

  // Set up for multithreaded processing.
  DenseFDThreadStruct str;
  str.Filter = this;
  str.TimeStep = NumericTraits<TimeStepType>::Zero;  // Not used during the
  // calculate change step.
  this->GetMultiThreader()->SetNumberOfWorkUnits(this->GetNumberOfWorkUnits());
  this->GetMultiThreader()->SetSingleMethod(this->CalculateChangeThreaderCallback,
                                            &str);

  // Initialize the list of time step values that will be generated by the
  // various threads.  There is one distinct slot for each possible thread,
  // so this data structure is thread-safe.
  threadCount = this->GetMultiThreader()->GetNumberOfWorkUnits();
  str.TimeStepList.resize(threadCount);                 
  str.ValidTimeStepList.resize(threadCount);
  str.ValidTimeStepList.resize( threadCount, false );
  
  // Multithread the execution
  this->GetMultiThreader()->SingleMethodExecute();

  // Resolve the single value time step to return
  dt = this->ResolveTimeStep(str.TimeStepList, str.ValidTimeStepList);

  // Explicitely call Modified on m_UpdateBuffer here
  // since ThreadedCalculateChange changes this buffer
  // through iterators which do not increment the
  // update buffer timestamp
  this->m_UpdateBuffer->Modified();
  
  return  dt;
}

template <class TInputImage, class TOutputImage>
ITK_THREAD_RETURN_FUNCTION_CALL_CONVENTION
DenseFiniteDifferenceImageFilter2<TInputImage, TOutputImage>
::CalculateChangeThreaderCallback( void * arg )
{
  DenseFDThreadStruct * str;
  int total, threadId, threadCount;

  threadId = ((MultiThreaderBase::WorkUnitInfo *)(arg))->WorkUnitID;
  threadCount = ((MultiThreaderBase::WorkUnitInfo *)(arg))->NumberOfWorkUnits;

  str = (DenseFDThreadStruct *)(((MultiThreaderBase::WorkUnitInfo *)(arg))->UserData);

  // Execute the actual method with appropriate output region
  // first find out how many pieces extent can be split into.
  // Using the SplitRequestedRegion method from itk::ImageSource.
  ThreadRegionType splitRegion;

  total = str->Filter->SplitRequestedRegion(threadId, threadCount,
                                            splitRegion);

  if (threadId < total)
    { 
    str->TimeStepList[threadId]
      = str->Filter->ThreadedCalculateChange(splitRegion, threadId);
    str->ValidTimeStepList[threadId] = true;
    }

  return ITK_THREAD_RETURN_DEFAULT_VALUE;
}

template <class TInputImage, class TOutputImage>
void
DenseFiniteDifferenceImageFilter2<TInputImage, TOutputImage>
::ThreadedApplyUpdate(TimeStepType dt, const ThreadRegionType &regionToProcess,
                      ThreadIdType)
{
  ImageRegionIterator<UpdateBufferType> u(m_UpdateBuffer,    regionToProcess);
  ImageRegionIterator<OutputImageType>  o(this->GetOutput(), regionToProcess);

  u.GoToBegin();
  o.GoToBegin();

  while ( !u.IsAtEnd() )
    {
    o.Value() += static_cast<PixelType>(u.Value() * dt);  // no adaptor support here
    ++o;
    ++u;
    }
}

template <class TInputImage, class TOutputImage>
typename
DenseFiniteDifferenceImageFilter2<TInputImage, TOutputImage>::TimeStepType
DenseFiniteDifferenceImageFilter2<TInputImage, TOutputImage>
::ThreadedCalculateChange(const ThreadRegionType &regionToProcess, ThreadIdType)
{
  typedef typename OutputImageType::SizeType   SizeType;
  typedef typename FiniteDifferenceFunctionType::NeighborhoodType
    NeighborhoodIteratorType;
  typedef ImageRegionIterator<UpdateBufferType> UpdateIteratorType;

  typename OutputImageType::Pointer output = this->GetOutput();
  TimeStepType timeStep;
  void *globalData;

  // Get the FiniteDifferenceFunction to use in calculations.
  const typename FiniteDifferenceFunctionType::Pointer df
    = this->GetDifferenceFunction();
  const SizeType  radius = df->GetRadius();
  

  // Ask the function object for a pointer to a data structure it
  // will use to manage any global values it needs.  We'll pass this
  // back to the function object at each calculation and then
  // again so that the function object can use it to determine a
  // time step for this iteration.
  globalData = df->GetGlobalDataPointer();

  // Process the non-boundary region.
  NeighborhoodIteratorType nD(radius, output, regionToProcess);
  UpdateIteratorType       nU(m_UpdateBuffer,  regionToProcess);
  nD.GoToBegin();
  while( !nD.IsAtEnd() )
    {
    nU.Value() = df->ComputeUpdate(nD, globalData);
    ++nD;
    ++nU;
    }

  // Ask the finite difference function to compute the time step for
  // this iteration.  We give it the global data pointer to use, then
  // ask it to free the global data memory.
  timeStep = df->ComputeGlobalTimeStep(globalData);
  df->ReleaseGlobalDataPointer(globalData);

  return timeStep;
}

template <class TInputImage, class TOutputImage>
void
DenseFiniteDifferenceImageFilter2<TInputImage, TOutputImage>
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  
}

}// end namespace itk

#endif
