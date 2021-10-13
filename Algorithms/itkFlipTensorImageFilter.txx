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
#ifndef _itk_FlipTensorImageFilter_txx_
#define _itk_FlipTensorImageFilter_txx_
#include "itkFlipTensorImageFilter.h"

#include <itkImageRegionConstIterator.h>
#include <itkImageRegionIterator.h>

namespace itk
{

  template <class TInputImage, class TOutputImage>
  FlipTensorImageFilter<TInputImage, TOutputImage>
  ::FlipTensorImageFilter()
  {
    // Set the axes to be flipped to NULL
    m_FlipAxes = new bool[ImageDimension];
    for (unsigned int i=0; i<ImageDimension; i++)
      m_FlipAxes[i]=false;
    
    for( unsigned int i=0; i<ImageDimension; i++ )
      m_NeighborhoodRadius[i] = 1;

    this->InPlaceOff();
    
  }
  
  template <class TInputImage, class TOutputImage>
  FlipTensorImageFilter<TInputImage, TOutputImage>
  ::~FlipTensorImageFilter()
  {
    delete [] m_FlipAxes;
  }
  

  template<class TInputImage, class TOutputImage>
  void
  FlipTensorImageFilter<TInputImage,TOutputImage>
  ::DynamicThreadedGenerateData(const OutputImageRegionType& outputRegionForThread)
  {
    
    typedef ImageRegionConstIterator<InputImageType>   InputIteratorType;
    typedef ImageRegionIterator<OutputImageType>       OutputIteratorType;
    
    InputIteratorType itIn(this->GetInput(), outputRegionForThread);
    OutputIteratorType itOut(this->GetOutput(), outputRegionForThread);

    while ( ! itOut.IsAtEnd() )
    {
      if( this->GetAbortGenerateData() )
        throw itk::ProcessAborted(__FILE__,__LINE__);
      
      InputPixelType T    = itIn.Get();
      OutputPixelType out = T;
      
      // Proceed the flip among the axes set in m_FlipAxes
      for (unsigned int axis=0; axis<ImageDimension; axis++)
      {
        if (m_FlipAxes[axis])
        {
          if (!T.IsZero())
          {
            // Proceed among the column axis
            for (unsigned int j=0; j<axis; j++)
              out.SetComponent ( axis, j, (-1*out.GetComponent (axis, j)) );
            
            // Proceed among the line axis
            for (unsigned int i=axis+1; i<ImageDimension; i++)
              out.SetComponent ( axis, i, (-1*out.GetComponent (axis, i)) );            
          }
        }
      }
      
      itOut.Set ( out );
      ++itOut;
      ++itIn;
    }     
  }
  
  
  

} // end of namespace itk


#endif
