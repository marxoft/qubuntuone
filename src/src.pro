TEMPLATE = lib

#unix:INSTALL_PREFIX = /usr

include(../qubuntuone.pri)

QT += network

TARGET = qubuntuone
DESTDIR = ../lib

contains(MEEGO_EDITION,harmattan) {
    CONFIG += staticlib libtuiclient
    DEFINES += QUBUNTUONE_STATIC_LIBRARY
} else {
    CONFIG += create_prl
    DEFINES += QUBUNTUONE_LIBRARY
}

SOURCES += \
    account.cpp \
    album.cpp \
    album_p.cpp \
    albumlist.cpp \
    albumlist_p.cpp \
    artist.cpp \
    artist_p.cpp \
    artistlist.cpp \
    artistlist_p.cpp \
    artwork.cpp \
    artwork_p.cpp \
    authentication.cpp \
    files.cpp \
    filetransfer.cpp \
    filetransfer_p.cpp \
    json.cpp \
    music.cpp \
    musicstream.cpp \
    musicstream_p.cpp \
    networkaccessmanager.cpp \
    node.cpp \
    node_p.cpp \
    nodelist.cpp \
    nodelist_p.cpp \
    oauth.cpp \
    playlist.cpp \
    playlist_p.cpp \
    playlistlist.cpp \
    playlistlist_p.cpp \
    reply.cpp \
    song.cpp \
    song_p.cpp \
    songlist.cpp \
    songlist_p.cpp \
    storagequota.cpp \
    token.cpp \
    user.cpp \
    user_p.cpp \
    useraccount.cpp \
    useraccount_p.cpp

HEADERS += \
    account.h \
    album.h \
    album_p.h \
    albumlist.h \
    albumlist_p.h \
    artist.h \
    artist_p.h \
    artistlist.h \
    artistlist_p.h \
    artwork.h \
    artwork_p.h \
    authentication.h \
    authentication_p.h \
    files.h \
    filetransfer.h \
    filetransfer_p.h \
    json.h \
    music.h \
    musicstream.h \
    musicstream_p.h \
    networkaccessmanager.h \
    node.h \
    node_p.h \
    nodelist.h \
    nodelist_p.h \
    oauth.h \
    playlist.h \
    playlist_p.h \
    playlistlist.h \
    playlistlist_p.h \
    qubuntuone_global.h \
    reply.h \
    reply_p.h \
    song.h \
    song_p.h \
    songlist.h \
    songlist_p.h \
    storagequota.h \
    storagequota_p.h \
    token.h \
    token_p.h \
    urls.h \
    user.h \
    user_p.h \
    useraccount.h \
    useraccount_p.h

headers.files = \
    account.h \
    album.h \
    albumlist.h \
    artist.h \
    artistlist.h \
    artwork.h \
    authentication.h \
    files.h \
    filetransfer.h \
    music.h \
    musicstream.h \
    node.h \
    nodelist.h \
    playlist.h \
    playlistlist.h \
    qubuntuone_global.h \
    reply.h \
    replyerror.h \
    song.h \
    songlist.h \
    storagequota.h \
    token.h \
    user.h \
    useraccount.h

!isEmpty(INSTALL_PREFIX) {
    target.path = $$INSTALL_PREFIX/lib
    headers.path = $$INSTALL_PREFIX/include/qubuntuone

    INSTALLS += target headers
}

symbian {
  #export public header to \epocroot\epoc32\include to be able to use them
  headers.path = $$PWD/qubuntuone
  for(header, headers.files) {
    {BLD_INF_RULES.prj_exports += "$$header"}
  }

  TARGET.EPOCALLOWDLLDATA = 1
  # uid for the dll
  #TARGET.UID3=
  TARGET.CAPABILITY = ReadDeviceData WriteDeviceData

  # add dll to the sis
  QUbuntuOneDeployment.sources = $${TARGET}.dll
  QUbuntuOneDeployment.path = /sys/bin

  DEPLOYMENT += QUbuntuOneDeployment
}
