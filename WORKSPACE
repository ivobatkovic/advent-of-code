load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
  name = "com_google_googletest",
  urls = ["https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip"],
  strip_prefix = "googletest-release-1.12.1",
  sha256 = "24564e3b712d3eb30ac9a85d92f7d720f60cc0173730ac166f27dda7fed76cb2"
)


_RULES_BOOST_COMMIT = "652b21e35e4eeed5579e696da0facbe8dba52b1f"

http_archive(
    name = "com_github_nelhage_rules_boost",
    sha256 = "c1b8b2adc3b4201683cf94dda7eef3fc0f4f4c0ea5caa3ed3feffe07e1fb5b15",
    strip_prefix = "rules_boost-%s" % _RULES_BOOST_COMMIT,
    urls = [
        "https://github.com/nelhage/rules_boost/archive/%s.tar.gz" % _RULES_BOOST_COMMIT,
    ],
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()

http_archive(
    name = "rules_foreign_cc",
    sha256 = "e14a159c452a68a97a7c59fa458033cc91edb8224516295b047a95555140af5f",
    strip_prefix = "rules_foreign_cc-0.4.0",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/0.4.0.tar.gz",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies()

http_archive(
  name = "ftxui",
  build_file = "//bazel:BUILD.ftxui.bazel",
  strip_prefix = "FTXUI-3.0.0",
  urls = ["https://github.com/ArthurSonzogni/FTXUI/archive/refs/tags/v3.0.0.tar.gz"],
  sha256 = "a8f2539ab95caafb21b0c534e8dfb0aeea4e658688797bb9e5539729d9258cc1",
)

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
# Hedron's Compile Commands Extractor for Bazel
# https://github.com/hedronvision/bazel-compile-commands-extractor
http_archive(
    name = "hedron_compile_commands",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/ed994039a951b736091776d677f324b3903ef939.tar.gz",
    strip_prefix = "bazel-compile-commands-extractor-ed994039a951b736091776d677f324b3903ef939",
    sha256="085bde6c5212c8c1603595341ffe7133108034808d8c819f8978b2b303afc9e7"
)
load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")
hedron_compile_commands_setup()
