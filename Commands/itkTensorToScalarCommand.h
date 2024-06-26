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
#ifndef _itk_TensorToScalarCommand_h_
#define _itk_TensorToScalarCommand_h_

#include "itkCommandObjectBase.h"

#include <ttkCommands/ttkCommandsExport.h>

namespace itk
{

  class TTKCOMMANDS_EXPORT TensorToScalarCommand : public CommandObjectBase
  {
    
  public:
		
    typedef TensorToScalarCommand Self;
    typedef CommandObjectBase Superclass;
    typedef SmartPointer <Self> Pointer;
    typedef SmartPointer <const Self> ConstPointer;
    
    itkTypeMacro(TensorToScalarCommand, CommandObjectBase);
    itkNewMacro(Self);
    
    const char *GetCommandName(void)
    { return "scalar"; }
    
    int Execute(int nargs, const char *args[]);
    
  protected:
    TensorToScalarCommand();
    ~TensorToScalarCommand();
    
  private:
    TensorToScalarCommand(const Self&);
    void operator=(const Self&);
    
  };
  
}

#endif
