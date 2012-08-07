//---------------------------------------------------------------------------//
/*!
 * \file   DTK_Assertion.hpp
 * \author Stuart Slattery
 * \brief  Assertions and Design-by-Contract for error handling.
 */
//---------------------------------------------------------------------------//

#ifndef DTK_ASSERTION_HPP
#define DTK_ASSERTION_HPP

#include <stdexcept>
#include <string>

#include <DataTransferKit_config.hpp>

namespace DataTransferKit
{
//---------------------------------------------------------------------------//
/*!
 * \brief Base class for DTK assertions. This structure is heavily based on
 * that in Nemesis developed by Tom Evans. We derive from std::logic_error
 * here as the DBC checks that utilize this class are meant to find errors
 * that can be prevented before runtime.
 */
//---------------------------------------------------------------------------//
class Assertion : public std::logic_error
{
  public:

    /*! 
     * \brief Default constructor.
     */
    Assertion( const std::string& msg )
	: std::logic_error( msg )
    { /* ... */ }

    /*! 
     * \brief DBC constructor.
     */
    Assertion( const std::string& cond, const std::string& file, 
	       const int line )
	: std::logic_error( generate_output( cond, file, line ) )
    { /* ... */ }

    //! Destructor.
    virtual ~Assertion() throw()
    { /* ... */ }

  private:

    // Build an assertion output from advanced constructor arguments.
    std::string generate_output( const std::string& cond, 
				 const std::string& file, 
				 const int line ) const;
};

//---------------------------------------------------------------------------//
// Throw functions.
//---------------------------------------------------------------------------//
// Throw a DataTransferKit::Assertion.
void throwAssertion( const std::string& cond, const std::string& file,
		     const int line );

//---------------------------------------------------------------------------//

} // end namespace DataTransferKit

//---------------------------------------------------------------------------//
// Design-by-Contract macros.
//---------------------------------------------------------------------------//
/*!
 * \page DataTransferKit Design-by-Contract.
 *
 * Design-by-Contract (DBC) functionality is provided to verify function
 * preconditions, postconditions, and invariants. These checks are separated
 * from the debug build and can be activated for both release and debug
 * builds. They can be activated by setting the following in a CMake
 * configure:
 *
 * -D DataTransferKit_ENABLE_DBC:BOOL=ON
 *
 * By default, DBC is deactivated. Although they will require additional
 * computational overhead, these checks provide a mechanism for veryifing
 * library input arguments. Note that the bounds-checking functionality used
 * within the DataTransferKit is only provided by a debug build.
 */

#if HAVE_DTK_DBC

#define testPrecondition(c) \
    if (!(c)) DataTransferKit::throwAssertion( #c, __FILE__, __LINE__ )
#define testPostcondition(c) \
    if (!(c)) DataTransferKit::throwAssertion( #c, __FILE__, __LINE__ )
#define testInvariant(c) \
    if (!(c)) DataTransferKit::throwAssertion( #c, __FILE__, __LINE__ )

#else

#define testPrecondition(c)
#define testPostcondition(c)
#define testInvariant(c)

#endif

//---------------------------------------------------------------------------//

#endif // end DTK_ASSERTION_HPP

//---------------------------------------------------------------------------//
// end DTK_Assertion.hpp
//---------------------------------------------------------------------------//
