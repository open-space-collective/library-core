////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           OpenSpaceToolkit/Core/Logger/Sinks/Console.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Core_Logger_Sinks_Console__
#define __OpenSpaceToolkit_Core_Logger_Sinks_Console__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/Types/Unique.hpp>
#include <OpenSpaceToolkit/Core/Logger/Sinks/Sink.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace core
{
namespace logger
{
namespace sinks
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Unique ;
using ostk::core::logger::Severity ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Log console sink

class Console : public Sink
{

    public:

        enum class Color
        {

            Black,
            Red,
            Green,
            Yellow,
            Blue,
            Magenta,
            Cyan,
            LightGray,
            DarkGray,
            LightRed,
            LightGreen,
            LightYellow,
            LightBlue,
            LightMagenta,
            LightCyan,
            White

        } ;

                                Console                                     (   const   Severity&                   aSeverity                                   ) ;

                                Console                                     (   const   Console&                    aConsole                                    ) ;

        virtual                 ~Console                                    ( ) override ;

        virtual Console*        clone                                       ( ) const override ;

        virtual void            enable                                      ( ) override ;
        virtual void            disable                                     ( ) override ;

        static String            ColorizeMessage                            (   const   String&                     aMessage,
                                                                                const   Console::Color&             aColor                                      ) ;

    private:

        class Impl ;

        friend class Console::Impl ;

        Unique<Console::Impl>   implUPtr_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
