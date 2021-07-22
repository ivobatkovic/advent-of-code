load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
  name = "com_google_googletest",
  urls = ["https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip"],
  strip_prefix = "googletest-609281088cfefc76f9d0ce82e1ff6c30cc3591e5",
)

new_local_repository(
  name = "boost",
  path = ".",
  build_file = "bazel/boost.BUILD"
)
new_local_repository(
  name = "boost_linux",
  path = "/usr/",
  build_file = "bazel/boost_linux.BUILD"
)
new_local_repository(
  name = "boost_osx",
  path = "/usr/local/",
  build_file = "bazel/boost_osx.BUILD"
)

new_local_repository(
  name = "ncurses",
  path = ".",
  build_file = "bazel/ncurses.BUILD"
)
new_local_repository(
  name = "ncurses_linux",
  path = "/usr/",
  build_file = "bazel/ncurses_linux.BUILD"
)
new_local_repository(
  name = "ncurses_osx",
  path = "/usr/local/opt/ncurses",
  build_file = "bazel/ncurses_osx.BUILD"
)