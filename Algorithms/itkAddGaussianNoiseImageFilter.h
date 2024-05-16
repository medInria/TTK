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
#ifndef _itk_AddGaussianNoiseImageFilter_h_
#define _itk_AddGaussianNoiseImageFilter_h_

#include <itkImageToImageFilter.h>
#include <itkImage.h>
#include <itkNormalVariateGenerator.h>

namespace itk
{


  template <class TInputImage, class TOutputImage>
    class ITK_EXPORT AddGaussianNoiseImageFilter :
  public ImageToImageFilter<TInputImage, TOutputImage>
  {

  public:

    /** Standard class type aliases. */
    using Self = AddGaussianNoiseImageFilter;
    using Superclass = ImageToImageFilter<TInputImage, TOutputImage>;
    using Pointer = SmartPointer<Self>;
    using ConstPointer = SmartPointer<const Self>;

    /** Method for creation through the object factory. */
    itkNewMacro(Self);

    /** Run-time type information (and related methods). */
    itkTypeMacro (AddGaussianNoiseImageFilter, ImageToImageFilter);

    typedef TInputImage                           InputImageType;
    typedef typename InputImageType::PixelType    InputPixelType;
    typedef TOutputImage                          OutputImageType;
    typedef typename OutputImageType::PixelType   OutputPixelType;
    typedef typename OutputImageType::RegionType  OutputRegionType;
    typedef typename InputImageType::Pointer      InputImagePointer;

    itkSetMacro (Variance, double);
    itkGetMacro (Variance, double);

    itkGetObjectMacro (NormalGenerator, Statistics::NormalVariateGenerator);
    itkSetObjectMacro (NormalGenerator, Statistics::NormalVariateGenerator);
    
    
  protected:
    AddGaussianNoiseImageFilter()
    {
      m_NormalGenerator = Statistics::NormalVariateGenerator::New();      
      m_Variance = 1.0;
    }
    ~AddGaussianNoiseImageFilter(){};

    void GenerateData(void);
    void GenerateOutputInformation();
    void GenerateInputRequestedRegion() noexcept(false);
    
  private:
    AddGaussianNoiseImageFilter (const Self&);
    void operator=(const Self&);

    double m_Variance;
    
    typename Statistics::NormalVariateGenerator::Pointer m_NormalGenerator;
    
  };
  

} // end of namespace


#include "itkAddGaussianNoiseImageFilter.txx"

#endif
