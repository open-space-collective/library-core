////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           OpenSpaceToolkit/Core/Error/RuntimeError.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Core_Error_RuntimeError__
#define __OpenSpaceToolkit_Core_Error_RuntimeError__

#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Error/Exception.hpp>

#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace core
{
namespace error
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::String ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Runtime error class

class RuntimeError : public Exception
{

    public:

                                RuntimeError                                (   const   String&                     aMessage                                    ) ;

                                // RuntimeError                                (   const   String&                     aScope,
                                //                                                 const   String&                     aMessage                                    ) ;

                                template <typename ...Args>
                                RuntimeError                                (   const   char*                       aFormat,
                                                                                        Args...                     anArgumentList                              )
                                :   Exception(String::Empty()),
                                    message_(String::Format(aFormat, anArgumentList...))
        {

        }

        //                         template <typename ...Args>
        //                         RuntimeError                                (   const   String&                     aScope,
        //                                                                         const   char*                       aFormat,
        //                                                                                 Args...                     anArgumentList                              )
        //                         :   Exception(aScope),
        //                             message_(String::Format(aFormat, anArgumentList...))
        // {

        // }

                                ~RuntimeError                               ( ) ;

        virtual const char*     what                                        ( ) const noexcept override ;

    private:

        String                  message_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
