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
#ifndef _itk_TensorsToDWITensorImageFilter_txx_
#define _itk_TensorsToDWITensorImageFilter_txx_
#endif

#include "itkTensorsToDWITensorImageFilter.h"
#include <itkImageRegionIterator.h>
#include <itkImageRegionConstIterator.h>

namespace itk
{


  template <class TInputImage, class TOutputImage>
  void
  TensorsToDWITensorImageFilter<TInputImage, TOutputImage>
  ::BeforeThreadedGenerateData()
  {

    if( m_GradientList.size()==0 )
    {
      throw itk::ExceptionObject (__FILE__,__LINE__,"Error: gradient list is empty, cannot generate DWI.");      
    }

    if( m_BaselineImage.IsNull() )
    {
      throw itk::ExceptionObject (__FILE__,__LINE__,"Error: Baseline is not set, cannot generate DWI.");
    }    

  }
  
  
  

  template <class TInputImage, class TOutputImage>
  void
  TensorsToDWITensorImageFilter<TInputImage, TOutputImage>
  ::DynamicThreadedGenerateData ( const OutputImageRegionType &outputRegionForThread)
  {

    
    typedef ImageRegionIterator<OutputImageType>      IteratorOutputType;
    typedef ImageRegionConstIterator<InputImageType>  IteratorInputType;
    
    unsigned int NOutput = this->GetNumberOfRequiredOutputs();
        
    std::vector<IteratorOutputType> IteratorOutputList;
    for( unsigned int i=0; i<NOutput; i++)
    {
      IteratorOutputType itOut (this->GetOutput(i), outputRegionForThread);
      IteratorOutputList.push_back (itOut);
    }
    IteratorInputType  itIn (this->GetInput(), outputRegionForThread);
    IteratorOutputType itB0 (this->GetBaselineImage(), outputRegionForThread);
    
    while(!itIn.IsAtEnd())
    {
      
      if( this->GetAbortGenerateData() )
      {
        throw itk::ProcessAborted(__FILE__,__LINE__);
      }
      
      
      InputPixelType T = itIn.Get();
      
      OutputPixelType b0 = itB0.Get();
      
      for( unsigned int i=0; i<NOutput; i++)
      {
        OutputPixelType out = static_cast<OutputPixelType>(0.0);	
	
        if( b0 > 0)
        {
	  out = static_cast<OutputPixelType>( b0*exp ( -1.0 * m_BValue * T.ScalarProductWith (m_GradientList [i]) ) );
        }
        
        IteratorOutputList[i].Set (out);
        ++(IteratorOutputList[i]);
      }
      
      ++itB0;
      ++itIn;
        
    }
  }
  
  

} // end of namespace
