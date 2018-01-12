################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/controlleur/App.cpp \
../src/controlleur/CJeu.cpp \
../src/controlleur/CLua.cpp \
../src/controlleur/CNiveau.cpp \
../src/controlleur/CPersonnage.cpp 

OBJS += \
./src/controlleur/App.o \
./src/controlleur/CJeu.o \
./src/controlleur/CLua.o \
./src/controlleur/CNiveau.o \
./src/controlleur/CPersonnage.o 

CPP_DEPS += \
./src/controlleur/App.d \
./src/controlleur/CJeu.d \
./src/controlleur/CLua.d \
./src/controlleur/CNiveau.d \
./src/controlleur/CPersonnage.d 


# Each subdirectory must supply rules for building sources it contributes
src/controlleur/%.o: ../src/controlleur/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1z -DWXUSINGDLL -D__WXGTK__ -DFILE_OFFSET_BITS=64 -I/usr/include/wx-3.0 -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/freetype2 -I/usr/include/harfbuzz -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/lib/wx/include/gtk3-unicode-3.0 -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


