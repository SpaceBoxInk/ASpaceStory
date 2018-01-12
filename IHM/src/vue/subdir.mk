################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/vue/AppFrame.cpp \
../src/vue/Caneva.cpp \
../src/vue/CustomWxTextCtrl.cpp \
../src/vue/ImagePanel.cpp \
../src/vue/ImagePanelP.cpp \
../src/vue/Tilemap.cpp \
../src/vue/VEnigma.cpp \
../src/vue/VInventory.cpp \
../src/vue/VItem.cpp \
../src/vue/VPlayerInventory.cpp \
../src/vue/VPrimitif.cpp \
../src/vue/wxSFMLCaneva.cpp 

OBJS += \
./src/vue/AppFrame.o \
./src/vue/Caneva.o \
./src/vue/CustomWxTextCtrl.o \
./src/vue/ImagePanel.o \
./src/vue/ImagePanelP.o \
./src/vue/Tilemap.o \
./src/vue/VEnigma.o \
./src/vue/VInventory.o \
./src/vue/VItem.o \
./src/vue/VPlayerInventory.o \
./src/vue/VPrimitif.o \
./src/vue/wxSFMLCaneva.o 

CPP_DEPS += \
./src/vue/AppFrame.d \
./src/vue/Caneva.d \
./src/vue/CustomWxTextCtrl.d \
./src/vue/ImagePanel.d \
./src/vue/ImagePanelP.d \
./src/vue/Tilemap.d \
./src/vue/VEnigma.d \
./src/vue/VInventory.d \
./src/vue/VItem.d \
./src/vue/VPlayerInventory.d \
./src/vue/VPrimitif.d \
./src/vue/wxSFMLCaneva.d 


# Each subdirectory must supply rules for building sources it contributes
src/vue/%.o: ../src/vue/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1z -DWXUSINGDLL -D__WXGTK__ -DFILE_OFFSET_BITS=64 -I/usr/include/wx-3.0 -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/freetype2 -I/usr/include/harfbuzz -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/lib/wx/include/gtk3-unicode-3.0 -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


