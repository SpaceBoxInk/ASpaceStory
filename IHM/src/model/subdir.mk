################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/model/MAssException.cpp \
../src/model/MCompetence.cpp \
../src/model/MCoordonnees.cpp \
../src/model/MEnigme.cpp \
../src/model/MEntite.cpp \
../src/model/MInventaire.cpp \
../src/model/MItem.cpp \
../src/model/MObjetTexture.cpp \
../src/model/MParameters.cpp \
../src/model/MPartieCouche.cpp \
../src/model/MPartieCoucheElement.cpp \
../src/model/MPersonnage.cpp \
../src/model/MRobot.cpp \
../src/model/MTerrain.cpp \
../src/model/MThreads.cpp \
../src/model/MTuile.cpp 

OBJS += \
./src/model/MAssException.o \
./src/model/MCompetence.o \
./src/model/MCoordonnees.o \
./src/model/MEnigme.o \
./src/model/MEntite.o \
./src/model/MInventaire.o \
./src/model/MItem.o \
./src/model/MObjetTexture.o \
./src/model/MParameters.o \
./src/model/MPartieCouche.o \
./src/model/MPartieCoucheElement.o \
./src/model/MPersonnage.o \
./src/model/MRobot.o \
./src/model/MTerrain.o \
./src/model/MThreads.o \
./src/model/MTuile.o 

CPP_DEPS += \
./src/model/MAssException.d \
./src/model/MCompetence.d \
./src/model/MCoordonnees.d \
./src/model/MEnigme.d \
./src/model/MEntite.d \
./src/model/MInventaire.d \
./src/model/MItem.d \
./src/model/MObjetTexture.d \
./src/model/MParameters.d \
./src/model/MPartieCouche.d \
./src/model/MPartieCoucheElement.d \
./src/model/MPersonnage.d \
./src/model/MRobot.d \
./src/model/MTerrain.d \
./src/model/MThreads.d \
./src/model/MTuile.d 


# Each subdirectory must supply rules for building sources it contributes
src/model/%.o: ../src/model/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1z -DWXUSINGDLL -D__WXGTK__ -DFILE_OFFSET_BITS=64 -I/usr/include/wx-3.0 -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/freetype2 -I/usr/include/harfbuzz -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/lib/wx/include/gtk3-unicode-3.0 -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


