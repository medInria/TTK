#ifndef _itk_RBFTensorExtrapolationCommandFactory_h_
#define _itk_RBFTensorExtrapolationCommandFactory_h_

#include "itkObjectFactoryBase.h"

namespace itk
{
  
  class RBFTensorExtrapolationCommandFactory : public ObjectFactoryBase
  {
    
  public:
    typedef RBFTensorExtrapolationCommandFactory Self;
    typedef ObjectFactoryBase        Superclass;
    typedef SmartPointer<Self>       Pointer;
    typedef SmartPointer<const Self> ConstPointer;
    
    /** Class methods used to interface with the registered factories. */
    virtual const char* GetITKSourceVersion(void) const;
    virtual const char* GetDescription(void) const;
    
    /** Method for class instantiation. */
    itkFactorylessNewMacro(Self);
    static RBFTensorExtrapolationCommandFactory* FactoryNew() { return new RBFTensorExtrapolationCommandFactory;}
    
    /** Run-time type information (and related methods). */
    itkTypeMacro(RBFTensorExtrapolationCommandFactory, ObjectFactoryBase);
    
    /** Register one factory of this type  */
    static void RegisterOneFactory(void)
    {
      RBFTensorExtrapolationCommandFactory::Pointer CSFFactory = RBFTensorExtrapolationCommandFactory::New();
      ObjectFactoryBase::RegisterFactory( CSFFactory );
    }
    
		
  protected:
    RBFTensorExtrapolationCommandFactory();
    ~RBFTensorExtrapolationCommandFactory();
    
  private:
    RBFTensorExtrapolationCommandFactory(const Self&);
    void operator=(const Self&);
    
  };
  
}

#endif
