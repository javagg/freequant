#ifndef FQ_VERSION_H
#define FQ_VERSION_H

namespace FreeQuant
{
  /// @brief Product information about QuickFAST
  const char FqDescription[] = "FreeQuant Version "
    "0.1.01"
    " (prerelease)"
    "\n"
    "Copyright (c) 2012 Alex Lee.\n"
    "All Rights Reserved\n"
    "See the file license.txt for licensing information.\n";
  /// @brief version number
  const long FqVersion = 0x00010401; // MMMM.mmpp {M=Major, m=minor, p=patch)
}
#endif // FQ_VERSION_H
