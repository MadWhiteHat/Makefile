CC=gcc
CC_FLAGS=-Wall -Wextra -g

ROOT_MAKEFILE_DIR = ${abspath ./}
PROJECT_NAME=text2png
PROJECT_SOURCE_DIR=${ROOT_MAKEFILE_DIR}/src
PROJECT_OUT_DIR=${ROOT_MAKEFILE_DIR}/out
PROJECT_EXTERNAL_DIR=${ROOT_MAKEFILE_DIR}/external
PROJECT_HEADERS=${PROJECT_SOURCE_DIR}/utility.h
PROJECT_SOURCES=${PROJECT_SOURCE_DIR}/main.c ${PROJECT_SOURCE_DIR}/utility.c
PROJECT_BUILD_DIR=${PROJECT_OUT_DIR}/build
PROJECT_BINARY_DIR=${PROJECT_BUILD_DIR}/${PROJECT_NAME}
PROJECT_EXECUTABLE_NAME=${PROJECT_NAME}.out

ZLIB_SOURCE_DIR=${PROJECT_EXTERNAL_DIR}/zlib
ZLIB_BINARY_DIR=${PROJECT_BUILD_DIR}/zlib
ZLIB_HEADERS_DIR=${ZLIB_SOURCE_DIR}
ZLIB_STATIC_LIBRARY=${ZLIB_BINARY_DIR}/libz.a
ZLIB_SHARED_LIBRARY=${ZLIB_BINARY_DIR}/libz.so

LIBPNG_SOURCE_DIR=${PROJECT_EXTERNAL_DIR}/libpng
LIBPNG_BINARY_DIR=${PROJECT_BUILD_DIR}/libpng
LIBPNG_HEADERS_DIR=${LIBPNG_SOURCE_DIR}
LIBPNG_STATIC_LIBRARY=${LIBPNG_BINARY_DIR}/libpng.a
LIBPNG_SHARED_LIBRARY=${LIBPNG_BINARY_DIR}/libpng.so

FREETYPE_SOURCE_DIR=${PROJECT_EXTERNAL_DIR}/freetype
FREETYPE_BINARY_DIR=${PROJECT_BUILD_DIR}/freetype
FREETYPE_HEADERS_DIR=${FREETYPE_SOURCE_DIR}/include
FREETYPE_STATIC_LIBRARY=${FREETYPE_BINARY_DIR}/libfreetype.a
FREETYPE_SHARED_LIBRARY=${FREETYPE_BINARY_DIR}/libfreetype.so

ELFLOADER_NAME=elfloader
ELFLOADER_SOURCE_DIR=${PROJECT_EXTERNAL_DIR}/${ELFLOADER_NAME}
ELFLOADER_BINARY_DIR=${PROJECT_BUILD_DIR}/${ELFLOADER_NAME}

CC_STATIC_FLAGS=-static -Werror
CC_DYNAMIC_FLAGS=-Werror -Wl,-rpath=${ZLIB_BINARY_DIR}
CC_BLOB_FLAGS=-fno-stack-protector -fno-exceptions -nostdlib -pie -fPIE -fPIC

--zlib ${ZLIB_SOURCE_DIR}:
	@echo "Building zlib..."
	@mkdir -p ${ZLIB_BINARY_DIR}
	@cmake \
	-DCMAKE_C_FLAGS=${ZLIB_FLAGS} \
	-Wno-deprecated \
	-S ${ZLIB_SOURCE_DIR} -B ${ZLIB_BINARY_DIR} 1> /dev/null
	@${MAKE} -C ${ZLIB_BINARY_DIR} ${ZLIB_TARGET} 1> /dev/null
	@echo "Done!"


--libpng: --zlib ${LIBPNG_SOURCE_DIR}
	@echo "Building libpng..."
	@mkdir -p ${LIBPNG_BINARY_DIR}
	@cmake \
	-DCMAKE_C_FLAGS=${LIBPNG_FLAGS} \
	-DPNG_EXECUTABLES=OFF \
	-DPNG_TESTS=OFF \
	-DPNG_BUILD_ZLIB=ON \
	-DZLIB_INCLUDE_DIRS=${ZLIB_HEADERS_DIR} \
	-DPNG_STATIC=${LIBPNG_BUILD_STATIC} \
	-DPNG_SHARED=${LIBPNG_BUILD_SHARED} \
	-DM_LIBRARY= \
	-Wno-deprecated \
	-S ${LIBPNG_SOURCE_DIR} -B ${LIBPNG_BINARY_DIR} 1> /dev/null
	@${MAKE} -C ${LIBPNG_BINARY_DIR} ${PNG_TARGET} 1> /dev/null
	@echo "Done!"

--freetype: ${FREETYPE_SOURCE_DIR}
	@echo "Building freetype..."
	@mkdir -p ${FREETYPE_BINARY_DIR}
	@cmake \
	-DCMAKE_C_FLAGS=${FREETYPE_FLAGS} \
	-DBUILD_SHARED_LIBS=${FREETYPE_BUILD_SHARED_LIBS} \
	-DFT_DISABLE_ZLIB=ON \
	-DFT_DISABLE_PNG=ON \
	-DFT_DISABLE_HARFBUZZ=ON \
	-DFT_DISABLE_BROTLI=ON \
	-DFT_DISABLE_BZIP2=ON \
	-S ${FREETYPE_SOURCE_DIR} -B ${FREETYPE_BINARY_DIR}
	@${MAKE} -C ${FREETYPE_BINARY_DIR} ${FREETYPE_TARGET}
	@echo "Done!"

--elf_loader: ${ELFLOADER_SOURCE_DIR}/Makefile
	@echo "Building elf loader..."
	@${MAKE} -C ${ELFLOADER_SOURCE_DIR} all 1> /dev/null
	@mkdir -p ${ELFLOADER_BINARY_DIR} 1> /dev/null
	@mv ${ELFLOADER_SOURCE_DIR}/${ELFLOADER_NAME} ${ELFLOADER_BINARY_DIR}/
	@ln -nsf ${ELFLOADER_BINARY_DIR}/${ELFLOADER_NAME} ${ELFLOADER_NAME}
	@echo "Done!"

git_update:
	@echo "Updating libraries..."
	@git submodule update --init --recursive --remote
	@echo "Done!"


--libs: --zlib --libpng --freetype

static: ZLIB_TARGET=zlibstatic
static: ZLIB_FLAGS=
static: LIBPNG_BUILD_STATIC=ON
static: LIBPNG_BUILD_SHARED=OFF
static: LIBPNG_TARGET=png_static
static: LIBPNG_FLAGS=
static: FREETYPE_BUILD_SHARED_LIBS=OFF
static: FREETYPE_TARGET=freetype
static: FREETYPE_FLAGS=
static: PROJECT_LINKAGE_TYPE=STATIC
static: --libs \
	${PROJECT_HEADERS} ${PROJECT_SOURCES}
	@echo "Building project with static linkage..."
	@mkdir -p ${PROJECT_BINARY_DIR}
	@${CC} ${CC_FLAGS} ${CC_STATIC_FLAGS} -D${PROJECT_LINKAGE_TYPE} \
		${PROJECT_SOURCES} \
		-I${LIBPNG_HEADERS_DIR} -I${FREETYPE_HEADERS_DIR} \
		${FREETYPE_STATIC_LIBRARY} ${LIBPNG_STATIC_LIBRARY} \
		${ZLIB_STATIC_LIBRARY} -lm \
		-o ${PROJECT_BINARY_DIR}/${PROJECT_EXECUTABLE_NAME}
	@ln -nsf ${PROJECT_BINARY_DIR}/${PROJECT_EXECUTABLE_NAME} \
		${PROJECT_EXECUTABLE_NAME}
	@echo "Done!"

dynamic: ZLIB_TARGET=zlib
dynamic: ZLIB_FLAGS=
dynamic: LIBPNG_BUILD_STATIC=OFF
dynamic: LIBPNG_BUILD_SHARED=ON
dynamic: LIBPNG_TARGET=png_shared
dynamic: LIBPNG_FLAGS=
dynamic: FREETYPE_BUILD_SHARED_LIBS=ON
dynamic: FREETYPE_TARGET=freetype
dynamic: FREETYPE_FLAGS=
dynamic: PROJECT_LINKAGE_TYPE=DYNAMIC
dynamic: --libs \
	${PROJECT_HEADERS} ${PROJECT_SOURCES}
	@echo "Building project with dynamic linkage..."
	@mkdir -p ${PROJECT_BINARY_DIR}
	${CC} ${CC_FLAGS} ${CC_DYNAMIC_FLAGS} -D${PROJECT_LINKAGE_TYPE} \
		-DLIBPNG_PATH='"${LIBPNG_SHARED_LIBRARY}"' \
		-DLIBFREETYPE_PATH='"${FREETYPE_SHARED_LIBRARY}"' \
		${PROJECT_SOURCES} \
		-I${LIBPNG_HEADERS_DIR} -I${FREETYPE_HEADERS_DIR} \
		-lz -lm -ldl \
		-o ${PROJECT_BINARY_DIR}/${PROJECT_EXECUTABLE_NAME}
	@ln -nsf ${PROJECT_BINARY_DIR}/${PROJECT_EXECUTABLE_NAME} \
		${PROJECT_EXECUTABLE_NAME}
	@echo "Done!"

blob: ZLIB_TARGET=zlibstatic
blob: ZLIB_FLAGS="${CC_BLOB_FLAGS}"
blob: LIBPNG_BUILD_STATIC=ON
blob: LIBPNG_BUILD_SHARED=OFF
blob: LIBPNG_TARGET=png_static
blob: LIBPNG_FLAGS="${CC_BLOB_FLAGS}"
blob: FREETYPE_BUILD_SHARED_LIBS=OFF
blob: FREETYPE_TARGET=freetype
blob: FREETYPE_FLAGS="${CC_BLOB_FLAGS}"
blob: PROJECT_LINKAGE_TYPE=BLOB
blob: --libs --elf_loader
	@echo "Building project with elfloader..."
	@mkdir -p ${PROJECT_BINARY_DIR}
	@${CC} ${CC_FLAGS} ${CC_BLOB_FLAGS} -e blob_entry	-D${PROJECT_LINKAGE_TYPE} \
		${PROJECT_SOURCES} \
		-I${ELFLOADER_SOURCE_DIR} -I${LIBPNG_HEADERS_DIR} -I${FREETYPE_HEADERS_DIR} \
		${FREETYPE_STATIC_LIBRARY} ${LIBPNG_STATIC_LIBRARY} \
		${ZLIB_STATIC_LIBRARY} \
		-o ${PROJECT_BINARY_DIR}/${PROJECT_EXECUTABLE_NAME}
	@ln -nsf ${PROJECT_BINARY_DIR}/${PROJECT_EXECUTABLE_NAME} \
		${PROJECT_EXECUTABLE_NAME}
	@echo "Done!"

clean:
	@echo "Cleaning up..."
	@rm -rf ${PROJECT_OUT_DIR}
	@rm -f ${PROJECT_EXECUTABLE_NAME}
	@rm -f ${ELFLOADER_NAME}
	@rm -f *.png
	@echo "Done!"
