TEMPLATE = subdirs
SUBDIRS = sub_src #sub_examples

sub_src.subdir = src
sub_examples.subdir = examples
sub_examples.depends = sub_src

contains(MEEGO_EDITION,harmattan) {
    OTHER_FILES += \
        qtc_packaging/debian_harmattan/rules \
        qtc_packaging/debian_harmattan/README \
        qtc_packaging/debian_harmattan/manifest.aegis \
        qtc_packaging/debian_harmattan/copyright \
        qtc_packaging/debian_harmattan/control \
        qtc_packaging/debian_harmattan/compat \
        qtc_packaging/debian_harmattan/changelog
}
