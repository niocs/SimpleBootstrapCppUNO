#include <stdio.h>
#include <sal/main.h>
#include <cppuhelper/bootstrap.hxx>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>

using namespace com::sun::star::uno;
using namespace com::sun::star::lang;

using ::rtl::OString;
using ::rtl::OUString;
using ::rtl::OUStringToOString;

SAL_IMPLEMENT_MAIN()
{
    try
    {
        // get the remote office component context
        Reference< XComponentContext > xContext( ::cppu::bootstrap() );
	if ( !xContext.is() )
	{
	    fprintf(stdout, "\nError getting context from running LO instance...\n");
	    return -1;
	}
	
	// retrieve the service-manager from the context
        Reference< XMultiComponentFactory > rServiceManager = xContext->getServiceManager();
	if ( rServiceManager.is() )
	    fprintf(stdout, "\nremote ServiceManager is available\n");
	else
	    fprintf(stdout, "\nremote ServiceManager is not available\n");
	fflush(stdout);
    }
    catch ( ::cppu::BootstrapException& e )
    {
        fprintf(stderr, "caught BootstrapException: %s\n",
                OUStringToOString( e.getMessage(), RTL_TEXTENCODING_ASCII_US ).getStr());
        return 1;
    }
    catch ( Exception& e )
    {
        fprintf(stderr, "caught UNO exception: %s\n",
                OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US ).getStr());
        return 1;
    }

    return 0;

}
