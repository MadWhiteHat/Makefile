CC=gcc
CC_FLAGS=-Wall -Wextra -pedantic -Werror

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

ZLIB_SORCE_DIR=${PROJECT_EXTERNAL_DIR}/zlib
ZLIB_BINARY_DIR=${PROJECT_BUILD_DIR}/zlib
ZLIB_HEADERS_DIR=${ZLIB_SORCE_DIR}
ZLIB_STATIC_LIBRARY=${ZLIB_BINARY_DIR}/libz.a
ZLIB_SHARED_LIBRARY=${ZLIB_BINARY_DIR}/libz.so

LIBPNG_SORCE_DIR=${PROJECT_EXTERNAL_DIR}/libpng
LIBPNG_BINARY_DIR=${PROJECT_BUILD_DIR}/libpng
LIBPNG_HEADERS_DIR=${LIBPNG_SORCE_DIR}
LIBPNG_STATIC_LIBRARY=${LIBPNG_BINARY_DIR}/libpng.a
LIBPNG_SHARED_LIBRARY=${LIBPNG_BINARY_DIR}/libpng.so

FREETYPE_SORCE_DIR=${PROJECT_EXTERNAL_DIR}/freetype
FREETYPE_BINARY_DIR=${PROJECT_BUILD_DIR}/freetype
FREETYPE_HEADERS_DIR=${FREETYPE_SORCE_DIR}/include
FREETYPE_STATIC_LIBRARY=${FREETYPE_BINARY_DIR}/libfreetype.a
FREETYPE_SHARED_LIBRARY=${FREETYPE_BINARY_DIR}/libfreetype.so

--zlib ${ZLIB_SOURCE_DIR}:
	@echo "Building zlib..."
	@mkdir -p ${ZLIB_BINARY_DIR}
	cmake \
	-Wno-deprecated \
	-S ${ZLIB_SORCE_DIR} -B ${ZLIB_BINARY_DIR}
	@${MAKE} -C ${ZLIB_BINARY_DIR} ${ZLIB_TARGET}
	@echo "Done!"


--libpng: --zlib ${LIBPNG_SORCE_DIR}
	@echo "Building libpng..."
	@mkdir -p ${LIBPNG_BINARY_DIR}
	cmake \
	-DPNG_EXECUTABLES=OFF \
	-DPNG_TESTS=OFF \
	-DPNG_BUILD_ZLIB=ON \
	-DZLIB_INCLUDE_DIRS=${ZLIB_HEADERS_DIR} \
	-DPNG_STATIC=${PNG_BUILD_STATIC} \
	-DPNG_SHARED=${PNG_BUILD_SHARED} \
	-DM_LIBRARY= \
	-Wno-deprecated \
	-S ${LIBPNG_SORCE_DIR} -B ${LIBPNG_BINARY_DIR}
	@${MAKE} -C ${LIBPNG_BINARY_DIR} ${PNG_TARGET}
	@echo "Done!"

--freetype: ${FREETYPE_SORCE_DIR}
	@echo "Building freetype..."
	@mkdir -p ${FREETYPE_BINARY_DIR}
	cmake \
	-DBUILD_SHARED_LIBS=${FREETYPE_BUILD_SHARED_LIBS} \
	-DFT_DISABLE_ZLIB=ON \
	-DFT_DISABLE_PNG=ON \
	-DFT_DISABLE_HARFBUZZ=ON \
	-DFT_DISABLE_BROTLI=ON \
	-DFT_DISABLE_BZIP2=ON \
	-S ${FREETYPE_SORCE_DIR} -B ${FREETYPE_BINARY_DIR}
	@${MAKE} -C ${FREETYPE_BINARY_DIR} ${FREETYPE_TARGET}
	@echo "Done!"

--git_update:
	@echo "Updating libraries..."
	@git submodule update --init --recursive --remote
	@echo "Done!"


--libs: --git_update --zlib --libpng --freetype

static: ZLIB_TARGET=zlibstatic
static: PNG_BUILD_STATIC=ON
static: PNG_BUILD_SHARED=OFF
static: PNG_TARGET=png_static
static: FREETYPE_BUILD_SHARED_LIBS=OFF
static: FREETYPE_TARGET=freetype
static: PROJECT_LINKAGE_TYPE=STATIC
static: --libs \
	${PROJECT_HEADERS} ${PROJECT_SOURCES}
	@echo "Building project with static linkage..."
	@mkdir -p ${PROJECT_BINARY_DIR}
	${CC} ${CC_FLAGS} -static -D${PROJECT_LINKAGE_TYPE} \
		${PROJECT_SOURCES} \
		-I${LIBPNG_HEADERS_DIR} -I${FREETYPE_HEADERS_DIR} \
		${FREETYPE_STATIC_LIBRARY} ${LIBPNG_STATIC_LIBRARY} \
		${ZLIB_STATIC_LIBRARY} -lm \
		-o ${PROJECT_BINARY_DIR}/${PROJECT_EXECUTABLE_NAME}
	@ln -s ${PROJECT_BINARY_DIR}/${PROJECT_EXECUTABLE_NAME} \
		${PROJECT_EXECUTABLE_NAME}
	@echo "Done!"

dynamic: ZLIB_TARGET=zlib
dynamic: PNG_BUILD_STATIC=OFF
dynamic: PNG_BUILD_SHARED=ON
dynamic: PNG_TARGET=png_shared
dynamic: FREETYPE_BUILD_SHARED_LIBS=ON
dynamic: FREETYPE_TARGET=freetype
dynamic: PROJECT_LINKAGE_TYPE=DYNAMIC
dynamic: --libs \
	${PROJECT_HEADERS} ${PROJECT_SOURCES}
	@echo "Building project with dynamic linkage..."
	@mkdir -p ${PROJECT_BINARY_DIR}
	${CC} ${CC_FLAGS} -D${PROJECT_LINKAGE_TYPE} \
		-DLIBPNG_PATH="${LIBPNG_DYNAMIC_LIBRARY}" \
		-DLIBFREETYPE_PATH="${FREETYPE_DYNAMIC_LIBRARY}" \
		${PROJECT_SOURCES} \
		-I${LIBPNG_HEADERS_DIR} -I${FREETYPE_HEADERS_DIR} \
		${FREETYPE_DYNAMIC_LIBRARY} ${LIBPNG_DYNAMIC_LIBRARY} \
		${ZLIB_DYNAMIC_LIBRARY} -lm -ldl\
		-o ${PROJECT_BINARY_DIR}/${PROJECT_EXECUTABLE_NAME}
	@ln -s ${PROJECT_BINARY_DIR}/${PROJECT_EXECUTABLE_NAME} \
		${PROJECT_EXECUTABLE_NAME}
	@echo "Done!"

clean:
	@echo "Cleaning up..."
	@rm -rf ${PROJECT_OUT_DIR}
	@rm -f ${PROJECT_EXECUTABLE_NAME}
	@rm -f *.png
	@echo "Done!"
