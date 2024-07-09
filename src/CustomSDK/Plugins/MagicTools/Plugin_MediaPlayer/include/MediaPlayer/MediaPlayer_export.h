#pragma once

#ifndef __MEDIAPLAYER_EXPORT_H__
# define __MEDIAPLAYER_EXPORT_H__

# ifdef _MSC_VER
#  ifdef MediaPlayer_EXPORTS
#   define MediaPlayer_API _declspec(dllexport)
#  elif defined USE_MediaPlayer_STATIC
#   define MediaPlayer_API
#  else
#   define MediaPlayer_API _declspec(dllimport)
#  endif // MediaPlayer_EXPORTS
# else
#  define MediaPlayer_API
# endif //_MSC_VER

#endif // !__MEDIAPLAYER_EXPORT_H__