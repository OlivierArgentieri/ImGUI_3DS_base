.PHONY: all all-classic format clean
.PHONY: dslink 3dslink 3dslink-classic nxlink-classic
.PHONY: 3dsx
.PHONY: release release-3dsx

export GITREV  := $(shell git rev-parse HEAD 2>/dev/null | cut -c1-6)
export VERSION_MAJOR := 0
export VERSION_MINOR := 0
export VERSION_MICRO := 0
export VERSION := $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_MICRO)

###########################################################################
all: 3dsx


format:
	@clang-format -style=file -i $(filter-out \
		include/imgui.h \
		source/imgui/imgui.cpp \
		source/imgui/imgui_demo.cpp \
		source/imgui/imgui_draw.cpp \
		source/imgui/imgui_internal.h \
		source/imgui/imgui_internal.h, \
		source/imgui/imgui_tables.cpp \
		source/imgui/imgui_widgets.cpp \
		source/imgui/imstb_rectpack.h \
		source/imgui/imstb_textedit.h \
		source/imgui/imstb_truetype.h \
		$(shell find source include -type f -name \*.c -o -name \*.cpp -o -name \*.h))

clean:
	@$(RM) 3ds/build/*

###########################################################################
3dsx:
	@$(MAKE) clean -f Makefile.3ds 3dsx

cia: 3dsx
	@$(MAKE) -f Makefile.3ds cia

###########################################################################
release: release-3dsx \
	@$(RM) -r release
	@mkdir release
	@xz -c <3ds/ftpd.3dsx >release/ftpd.3dsx.xz
	@ln -s ../3ds/ftpd.3dsx release/ftpd.3dsx

release-3dsx:
	@$(MAKE) -f Makefile.3ds 3dsx DEFINES=-DNDEBUG OPTIMIZE="-O3 -flto"
