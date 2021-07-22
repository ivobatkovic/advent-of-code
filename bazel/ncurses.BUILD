package(default_visibility = ["//visibility:public"])

cc_library(
    name = "ncurses-lib",
    deps =  select({
            "@platforms//os:osx" : [ "@ncurses_osx//:ncurses-lib"],
            "//conditions:default" : ["@ncurses_linux//:ncurses-lib"],
    }),
)
