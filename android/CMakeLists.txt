cmake_minimum_required(VERSION 3.4.1)  # for example
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/bindings/c
    ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/toolkit
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/asf
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/mpeg
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/ogg
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/ogg/flac
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/flac
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/mpc
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/mp4
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/ogg/vorbis
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/ogg/speex
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/ogg/opus
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/mpeg/id3v2
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/mpeg/id3v2/frames
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/mpeg/id3v1
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/ape
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/wavpack
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/trueaudio
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/riff
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/riff/aiff
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/riff/wav
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/mod
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/s3m
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/it
  ${CMAKE_CURRENT_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/xm
  ${CMAKE_SOURCE_DIR}/../miniaudio/taglib-ndk/taglib/3rdparty
)


set(mpeg_SRCS
../miniaudio/taglib-ndk/taglib/mpeg/mpegfile.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/mpegproperties.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/mpegheader.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/xingheader.cpp
)

set(id3v1_SRCS
../miniaudio/taglib-ndk/taglib/mpeg/id3v1/id3v1tag.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v1/id3v1genres.cpp
)

set(id3v2_SRCS
../miniaudio/taglib-ndk/taglib/mpeg/id3v2/id3v2framefactory.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/id3v2synchdata.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/id3v2tag.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/id3v2header.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/id3v2frame.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/id3v2footer.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/id3v2extendedheader.cpp
  )

set(frames_SRCS
../miniaudio/taglib-ndk/taglib/mpeg/id3v2/frames/attachedpictureframe.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/frames/commentsframe.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/frames/eventtimingcodesframe.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/frames/generalencapsulatedobjectframe.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/frames/ownershipframe.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/frames/popularimeterframe.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/frames/privateframe.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/frames/relativevolumeframe.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/frames/synchronizedlyricsframe.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/frames/textidentificationframe.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/frames/uniquefileidentifierframe.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/frames/unknownframe.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/frames/unsynchronizedlyricsframe.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/frames/urllinkframe.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/frames/chapterframe.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/frames/tableofcontentsframe.cpp
  ../miniaudio/taglib-ndk/taglib/mpeg/id3v2/frames/podcastframe.cpp
  )

set(ogg_SRCS
../miniaudio/taglib-ndk/taglib/ogg/oggfile.cpp
  ../miniaudio/taglib-ndk/taglib/ogg/oggpage.cpp
  ../miniaudio/taglib-ndk/taglib/ogg/oggpageheader.cpp
  ../miniaudio/taglib-ndk/taglib/ogg/xiphcomment.cpp
  )

set(vorbis_SRCS
../miniaudio/taglib-ndk/taglib/ogg/vorbis/vorbisfile.cpp
  ../miniaudio/taglib-ndk/taglib/ogg/vorbis/vorbisproperties.cpp
  )

set(flacs_SRCS
../miniaudio/taglib-ndk/taglib/flac/flacfile.cpp
  ../miniaudio/taglib-ndk/taglib/flac/flacpicture.cpp
  ../miniaudio/taglib-ndk/taglib/flac/flacproperties.cpp
  ../miniaudio/taglib-ndk/taglib/flac/flacmetadatablock.cpp
  ../miniaudio/taglib-ndk/taglib/flac/flacunknownmetadatablock.cpp
  )

set(oggflacs_SRCS
../miniaudio/taglib-ndk/taglib/ogg/flac/oggflacfile.cpp
  )

set(mpc_SRCS
../miniaudio/taglib-ndk/taglib/mpc/mpcfile.cpp
  ../miniaudio/taglib-ndk/taglib/mpc/mpcproperties.cpp
  )

set(mp4_SRCS
../miniaudio/taglib-ndk/taglib/mp4/mp4file.cpp
  ../miniaudio/taglib-ndk/taglib/mp4/mp4atom.cpp
  ../miniaudio/taglib-ndk/taglib/mp4/mp4tag.cpp
  ../miniaudio/taglib-ndk/taglib/mp4/mp4item.cpp
  ../miniaudio/taglib-ndk/taglib/mp4/mp4properties.cpp
  ../miniaudio/taglib-ndk/taglib/mp4/mp4coverart.cpp
  )


set(wavpack_SRCS
../miniaudio/taglib-ndk/taglib/wavpack/wavpackfile.cpp
  ../miniaudio/taglib-ndk/taglib/wavpack/wavpackproperties.cpp
  )

set(speex_SRCS
../miniaudio/taglib-ndk/taglib/ogg/speex/speexfile.cpp
  ../miniaudio/taglib-ndk/taglib/ogg/speex/speexproperties.cpp
  )


set(trueaudio_SRCS
../miniaudio/taglib-ndk/taglib/trueaudio/trueaudiofile.cpp
  ../miniaudio/taglib-ndk/taglib/trueaudio/trueaudioproperties.cpp
  )

set(asf_SRCS
../miniaudio/taglib-ndk/taglib/asf/asftag.cpp
  ../miniaudio/taglib-ndk/taglib/asf/asffile.cpp
  ../miniaudio/taglib-ndk/taglib/asf/asfproperties.cpp
  ../miniaudio/taglib-ndk/taglib/asf/asfattribute.cpp
  ../miniaudio/taglib-ndk/taglib/asf/asfpicture.cpp
  )


set(toolkit_SRCS
../miniaudio/taglib-ndk/taglib/toolkit/tstring.cpp
  ../miniaudio/taglib-ndk/taglib/toolkit/tstringlist.cpp
  ../miniaudio/taglib-ndk/taglib/toolkit/tbytevector.cpp
  ../miniaudio/taglib-ndk/taglib/toolkit/tbytevectorlist.cpp
  ../miniaudio/taglib-ndk/taglib/toolkit/tbytevectorstream.cpp
  ../miniaudio/taglib-ndk/taglib/toolkit/tiostream.cpp
  ../miniaudio/taglib-ndk/taglib/toolkit/tfile.cpp
  ../miniaudio/taglib-ndk/taglib/toolkit/tfilestream.cpp
  ../miniaudio/taglib-ndk/taglib/toolkit/tdebug.cpp
  ../miniaudio/taglib-ndk/taglib/toolkit/tpropertymap.cpp
  ../miniaudio/taglib-ndk/taglib/toolkit/trefcounter.cpp
  ../miniaudio/taglib-ndk/taglib/toolkit/tdebuglistener.cpp
  ../miniaudio/taglib-ndk/taglib/toolkit/tzlib.cpp
  )

if(HAVE_ZLIB_SOURCE)
  set(zlib_SRCS
    ${ZLIB_SOURCE}/adler32.c
    ${ZLIB_SOURCE}/crc32.c
    ${ZLIB_SOURCE}/inffast.c
    ${ZLIB_SOURCE}/inflate.c
    ${ZLIB_SOURCE}/inftrees.c
    ${ZLIB_SOURCE}/zutil.c
  )
endif()

set(tag_LIB_SRCS
  ${mpeg_SRCS} ${id3v1_SRCS} ${id3v2_SRCS} ${frames_SRCS} ${ogg_SRCS}
  ${vorbis_SRCS} ${oggflacs_SRCS} ${mpc_SRCS} ${toolkit_SRCS} ${flacs_SRCS}
  ${wavpack_SRCS} ${speex_SRCS} ${trueaudio_SRCS}
  ${asf_SRCS} ${mp4_SRCS}
  ${zlib_SRCS}
  ../miniaudio/taglib-ndk/taglib/tag.cpp
  ../miniaudio/taglib-ndk/taglib/tagunion.cpp
  ../miniaudio/taglib-ndk/taglib/fileref.cpp
  ../miniaudio/taglib-ndk/taglib/audioproperties.cpp
  ../miniaudio/taglib-ndk/taglib/tagutils.cpp
)

link_libraries(OpenSLES)
# link_libraries(aaudio)
add_library( native_player

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             ${tag_LIB_SRCS}
             ../miniaudio/taglib-ndk/bindings/c/tag_c.cpp
             ../miniaudio/taglib-ndk/bindings/c/tag_c.h
             ../miniaudio/miniplayer.c )
