/*------------------------------------------------------------------------------

   Copyright (c) 2000 Tyrell Corporation. All rights reserved.

   Tyrell DarkIce

   File     : BufferedSink.h
   Version  : $Revision$
   Author   : $Author$
   Location : $Source$
   
   Abstract : 

     A Sink First-In First-Out buffer
     This buffer can always be written to, it overwrites any
     data contained if needed
     The class is not thread-safe

   Copyright notice:

     This program is free software; you can redistribute it and/or
     modify it under the terms of the GNU General Public License  
     as published by the Free Software Foundation; either version 2
     of the License, or (at your option) any later version.
    
     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of 
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
     GNU General Public License for more details.
    
     You should have received a copy of the GNU General Public License
     along with this program; if not, write to the Free Software
     Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
     USA.

------------------------------------------------------------------------------*/
#ifndef BUFFERED_SINK_H
#define BUFFERED_SINK_H

#ifndef __cplusplus
#error This is a C++ include file
#endif


/* ============================================================ include files */

#include "Ref.h"
#include "Sink.h"


/* ================================================================ constants */


/* =================================================================== macros */


/* =============================================================== data types */

/*------------------------------------------------------------------------------
 *  
 *----------------------------------------------------------------------------*/
class BufferedSink : public Sink
{
    private:

        unsigned char     * buffer;
        unsigned char     * bufferEnd;
        unsigned int        bufferSize;

        unsigned char     * inp;
        unsigned char     * outp;


        Ref<Sink>           sink;


        void
        init (  Sink              * sink,
                unsigned int        size )          throw ( Exception );


        void
        strip ( void )                              throw ( Exception );


        inline unsigned char *
        slidePointer (
                        unsigned char * p,
                        unsigned int    offset )        throw ()
        {
            p += offset;
            while ( p >= bufferEnd ) {
                p -= bufferSize;
            }

            return p;
        }
        

    protected:

        inline
        BufferedSink ( void )                       throw ( Exception )
        {
            throw Exception( __FILE__, __LINE__);
        }


        inline unsigned int
        getSize ( void ) const                      throw ()
        {
            return bufferSize;
        }


        unsigned int
        store (     const void    * buffer,
                    unsigned int    bufferSize )    throw ( Exception );


    public:

        inline 
        BufferedSink (  Sink              * sink,
                        unsigned int        size )      throw ( Exception )
        {
            init( sink, size);
        }


        BufferedSink (  const BufferedSink &  buffer )  throw ( Exception );


        inline virtual
        ~BufferedSink ( void )                          throw ( Exception )
        {
            strip();
        }


        virtual BufferedSink &
        operator= ( const BufferedSink &    bs )        throw ( Exception );


        inline virtual BufferedSink *
        clone ( void ) const                            throw ( Exception )
        {
            return new BufferedSink(*this);
        }


        inline virtual bool
        open ( void )                                   throw ( Exception )
        {
            return sink->open();
        }


        inline virtual bool
        isOpen ( void ) const                           throw ( Exception )
        {
            return sink->isOpen();
        }


        inline virtual bool
        canWrite (     unsigned int    sec,
                       unsigned int    usec )           throw ( Exception )
        {
            return true;
        }


        virtual unsigned int
        write (    const void    * buf,
                   unsigned int    len )                throw ( Exception );


        inline virtual void
        flush ( void )                                  throw ( Exception )
        {
            unsigned char   b[0];

            write( b, 0);
        }


        virtual void
        close ( void )                                  throw ( Exception );
};


/* ================================================= external data structures */


/* ====================================================== function prototypes */



#endif  /* BUFFERED_SINK_H */


/*------------------------------------------------------------------------------
 
  $Source$

  $Log$
  Revision 1.1  2000/11/05 10:05:48  darkeye
  Initial revision

  
------------------------------------------------------------------------------*/

