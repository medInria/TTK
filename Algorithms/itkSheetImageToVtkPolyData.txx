/*=========================================================================

  Program:   Tensor ToolKit - TTK
  Module:    $URL: https://scm.gforge.inria.fr/svn/ttk/trunk/Algorithms/itkSheetImageToVtkPolyData.txx $
  Language:  C++
  Date:      $Date: 2010-12-22 10:25:59 +0000 (Wed, 22 Dec 2010) $
  Version:   $Revision: 124 $

  Copyright (c) INRIA 2010. All rights reserved.
  See LICENSE.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itk_SheetImageToVtkPolyData_txx_
#define _itk_SheetImageToVtkPolyData_txx_
#include "itkSheetImageToVtkPolyData.h"

#include <itkImageRegionIterator.h>

#include <itkContinuousIndex.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <itkImage.h>

namespace itk
{
  
  template<class TInputImage>
  SheetImageToVtkPolyData<TInputImage>::
  SheetImageToVtkPolyData()
  {
    m_Input = 0;
    m_Output = OutputType::New();
    m_Output->Allocate();
  }


  template<class TInputImage>
  SheetImageToVtkPolyData<TInputImage>::
  ~SheetImageToVtkPolyData()
  {
    m_Output->Delete();
  }


  template<class TInputImage>
  typename SheetImageToVtkPolyData<TInputImage>::OutputType*
  SheetImageToVtkPolyData<TInputImage>::
  GetOutput() const
  {
    return m_Output;
  }
  
  
  template<class TInputImage>
  void
  SheetImageToVtkPolyData<TInputImage>::
  Update()
  {
    if( !this->GetInput() )
    {
      throw itk::ExceptionObject (__FILE__,__LINE__,"Error: Input is not set.");
    }
    
    //m_Output->Reset();
    m_Output->Initialize();
    m_Output->Allocate();

    typedef ImageRegionConstIterator<InputImageType> InputIteratorType;
    InputIteratorType itIn (this->GetInput(), this->GetInput()->GetLargestPossibleRegion());
    
    vtkPoints*            myPoints     = vtkPoints::New();
    vtkUnsignedCharArray* myColors     = vtkUnsignedCharArray::New();
    vtkUnsignedCharArray* myCellColors = vtkUnsignedCharArray::New();
    vtkFloatArray*        myFAArray    = vtkFloatArray::New();
    vtkFloatArray*        tensorArray  = vtkFloatArray::New();
    myColors->SetNumberOfComponents (3);
    myCellColors->SetNumberOfComponents (3);
    myFAArray->SetName ("FA");
    myFAArray->SetNumberOfComponents (1);
    tensorArray->SetName ("Tensors");
    tensorArray->SetNumberOfComponents (6);
    
    unsigned long numPixels = this->GetInput()->GetLargestPossibleRegion().GetNumberOfPixels();
    unsigned long step      = numPixels/10;
    unsigned long progress  = 0;
    TensorType t;

    this->UpdateProgress (0.0);

    while( !itIn.IsAtEnd() )
    {
      SheetType Sheet               = itIn.Get();
      SheetPointListType listPoints = Sheet.GetPointList();
      int npts = (int)(listPoints.size());
      
      if(npts>1)
      {
        vtkIdType* ids = new vtkIdType[npts];

        // special case of the first point:
        VectorType diff = listPoints[1].Point-listPoints[0].Point;
        diff /= diff.GetNorm();
	
        double fa = 0.0;
        t = listPoints[0].Tensor;
        if (!t.IsZero())
        {
          fa = t.GetFA();
        }        
        
        //double alpha = 1.0;
        for( unsigned int i=0; i<3; i++)
        {
          //double c = 2.0*fabs (diff[i]*alpha)*255.0;
          double c = fabs (diff[i])*255.0;
          myColors->InsertNextValue( (unsigned char)( c>255.0?255.0:c ) );
        }
        myFAArray->InsertNextValue (fa);

	for (unsigned int i=0; i<6; i++)
	  tensorArray->InsertNextValue ( t[i] );
	
        //myColors->InsertNextValue( (unsigned char)(alpha*255.0) );
        //myColors->InsertNextValue( (unsigned char)(255.0) );
        
        PointType pt = listPoints[0].Point;
        ids[0] = myPoints->InsertNextPoint (pt[0],pt[1],pt[2]);
        
        if( npts>1)
        {
          for( int i=1; i<npts-1; i++)
          {            
            fa = 0.0;
            t = listPoints[i].Tensor;
            if (!t.IsZero())
            {
              fa = t.GetFA();
            }
            
            diff = listPoints[i+1].Point-listPoints[i-1].Point;
            diff /= diff.GetNorm();
            for( unsigned int j=0; j<3; j++)
            {
              //double c = 2.0*fabs (diff[j]*alpha)*255.0;
              double c = fabs (diff[j])*255.0;
              myColors->InsertNextValue( (unsigned char)( c>255.0?255.0:c ) );
            }
            myFAArray->InsertNextValue (fa);

	    for (unsigned int j=0; j<6; j++)
	      tensorArray->InsertNextValue ( t[j] );
	    
            //myColors->InsertNextValue( (unsigned char)(alpha*255.0) );
            //myColors->InsertNextValue( (unsigned char)(255.0) );
            
            pt = listPoints[i].Point;
            ids[i] = myPoints->InsertNextPoint (pt[0],pt[1],pt[2]);
          }
          
          // special case of the last point
          
          fa = 0.0;
          t = listPoints[npts-1].Tensor;
          if (!t.IsZero())
          {
            fa = t.GetFA();
          }
          
          diff = listPoints[npts-2].Point-listPoints[npts-1].Point;
          diff /= diff.GetNorm();
          for( unsigned int i=0; i<3; i++)
          {
            //double c = 2.0*fabs (alpha*diff[i])*255;
            double c = fabs (diff[i])*255;
            myColors->InsertNextValue( (unsigned char)(c>255.0?255.0:c) );
          }
          myFAArray->InsertNextValue (fa);

	  for (unsigned int i=0; i<6; i++)
	    tensorArray->InsertNextValue ( t[i] );
	  
          //myColors->InsertNextValue( (unsigned char)(255.0*alpha) );
          //myColors->InsertNextValue( (unsigned char)(255.0) );
          
          pt = listPoints[npts-1].Point;
          ids[npts-1] = myPoints->InsertNextPoint (pt[0],pt[1],pt[2]);

        }
        
        //m_Output->InsertNextCell (VTK_POLY_LINE, npts, ids);

        // cell color
        PointType first = listPoints[0].Point;
        PointType last  = listPoints[npts-1].Point;
        diff = last-first;
        diff.Normalize();
        for( unsigned int i=0; i<3; i++)
        {
          double c = fabs ( diff[i] )*255;
          unsigned char color = (unsigned char)(c>255.0?255.0:c);
          myCellColors->InsertNextValue ( color );
        }
        
        delete [] ids;
	
      }
      

      if( step>0)
      {        
        if( (progress%step)==0 )
        {
          this->UpdateProgress ( double(progress)/double(numPixels) );
        }
      }
      
      ++itIn;
      ++progress;
    }

    m_Output->SetPoints (myPoints);
    m_Output->GetPointData()->SetScalars (myColors);
    m_Output->GetPointData()->AddArray   (tensorArray);
    m_Output->GetPointData()->AddArray   (myFAArray);
    // m_Output->GetCellData()->SetScalars  (myCellColors);
    
    myPoints->Delete();
    myColors->Delete();
    myCellColors->Delete();
    myFAArray->Delete();
    tensorArray->Delete();

    this->UpdateProgress (1.0);
    
  }
  
  
  
} // end of namespace

#endif
