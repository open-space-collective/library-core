////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           OpenSpaceToolkit/Core/Error/Runtime/Wrong.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Core_Error_Runtime_Wrong__
#define __OpenSpaceToolkit_Core_Error_Runtime_Wrong__

#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Error/RuntimeError.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace core
{
namespace error
{
namespace runtime
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::String ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Wrong variable error class

class Wrong : public RuntimeError
{

    public:

                                Wrong                                       (   const   String&                     aVariableName                               ) ;

                                template <typename ...Args>
                                Wrong                                       (   const   String&                     aVariableName,
                                                                                        Args...                     anArgumentList                              )
                                :   RuntimeError("{} = {} is wrong.", aVariableName, anArgumentList...)
        {

        }

                                // Wrong                                       (   const   String&                     aScope,
                                //                                                 const   String&                     aVariableName                               ) ;

                                ~Wrong                                      ( ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////