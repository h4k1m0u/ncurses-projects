#ifndef BLOCKS_HPP
#define BLOCKS_HPP

namespace Blocks {
  /**
   * wchar_t literal (can hold UTF-32 on linux, UTF-16 on windows)
   * Sorted from lightest to darkest (Light Shade is the darkest when rendered on the terminal!)
   * Can be rendered on terminal with: `$ echo -e '\u2588\u2593\u2592\u2591'`
   */

  /**
   * TODO: Better to use other characters for termux/Android (better rendering), which is detected based on __ANDROID__ macro
   * To get list of predefined macros: `$ ccp -dM - < /dev/null`
   * https://stackoverflow.com/a/8249232/2228912
   */
  constexpr wchar_t FULL_WCHAR = L'█';         // Full Block:  '\u2588'
  constexpr wchar_t DARK_SHADE_WCHAR = u'▓';   // Dark Shade:  '\u2593'
  constexpr wchar_t MEDIUM_SHADE_WCHAR = u'▒'; // Dark Shade:  '\u2592'
  constexpr wchar_t LIGHT_SHADE_WCHAR = u'░';  // Light Shade: '\u2591'
};

#endif
