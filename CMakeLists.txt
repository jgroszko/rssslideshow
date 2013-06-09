project(rssslideshow.kss)

cmake_minimum_required(VERSION 2.8)
find_package(KDE4 REQUIRED)
find_package(KDE4Workspace REQUIRED)

include (KDE4Defaults)

include_directories ( ${KDE4WORKSPACE_INCLUDE_DIR} ${KDE4_INCLUDES} )

set(rssslideshow.kss_SRCS RssSlideShowSaver.cpp
			  RssSlideShowSetup.cpp
			  RssSlideShowInterface.cpp
			  FeedReadWorker.cpp
			  main.cpp )

kde4_add_ui_files(rssslideshow.kss_SRCS rssslideshowcfg.ui )

kde4_add_executable(rssslideshow.kss ${rssslideshow.kss_SRCS})

target_link_libraries( rssslideshow.kss ${KDE4_KIO_LIBS} ${KDE4WORKSPACE_KSCREENSAVER_LIBRARY} ${QT_QTXMLPATTERNS_LIBRARY})

install(TARGETS rssslideshow.kss  ${INSTALL_TARGETS_DEFAULT_ARGS} )

install( FILES RSSSlideShow.desktop DESTINATION  ${SERVICES_INSTALL_DIR}/ScreenSavers )
