Configuring the T540p TouchPad and TrackPoint
=============================================

In this document I've documented the steps I took in ``$TITLE`` on
Debian Stretch.

# TrackPoint

Using the TrackPoint works out of the box on Debian Stretch, but
unfortunately you can't use it to scroll by default. To fix that, you
have to use the [evdev package from the ArchLinux distro][1], apply some
patches, then install it.

I tried using the gpointing-device-settings package to configure it, but
it always stack-smash crashes, see [this bug report][2].

To list all the input devices on your machine, then see and edit all the
configuration options available for it, just do the following.

```
xinput --list
xinput --list-props "$DEVICE_NAME"
```

Unfortunately on Debian Stretch you won't be able to set any ``Wheel
Emulation`` because these simply aren't available. You will need to
download, patch, compile, and install the evdev package I mentioned
earlier. Kudos to [this answer][3] on le'old askubuntu. To do the same
thing on Debian stretch, do the following:

```bash
sudo apt-get install git
sudo apt-get build-dep xserver-xorg-input-evdev xserver-xorg-input-synaptics

mkdir tmp-trackpoint
cd tmp-trackpoint

git clone https://aur.archlinux.org/xf86-input-evdev-trackpoint.git
git clone git://git.debian.org/git/pkg-xorg/driver/xserver-xorg-input-evdev
git clone git://git.debian.org/git/pkg-xorg/driver/xserver-xorg-input-synaptics

mv xf86-input-evdev-trackpoint arch
mv xserver-xorg-input-evdev evdev
mv xserver-xorg-input-synaptics synaptics

cp synaptics/src/{eventcomm.c,eventcomm.h,properties.c,synaptics.c,synapticsstr.h,synproto.c,synproto.h} evdev/src
cp synaptics/include/synaptics-properties.h evdev/src
cp arch/*.patch evdev

cd evdev
patch -p1 -i 0001-implement-trackpoint-wheel-emulation.patch
patch -p1 -i 0004-disable-clickpad_guess_clickfingers.patch
patch -p1 -i 0006-add-synatics-files-into-Makefile.am.patch

dpkg-buildpackage -d

cd ..
sudo dpkg -i xserver-xorg-input-evdev_*.deb
sudo apt-get remove xserver-xorg-input-synaptics

sudo mkdir /etc/X11/xorg.conf.d/
sudo cp arch/90-evdev-trackpoint.conf /etc/X11/xorg.conf.d
```

This didn't work out of the box, I ran into some compilation errors
because the ``xorg-server.h`` wasn't included in the ``eventcomm.h`` and
``synproto.h`` header files. After adding the ``#include``s, it worked.

# TouchPad

In order to test different configurations for the touchpad, I tried
disabling and enabling the device, but that didn't seem to work. The
only way to set new configs is to restart X11.

```
xinput disable $DEVICE_NAME
xinput enable  $DEVICE_NAME
```

## Setting button areas for clicking

This is the default configuration for the touchpad that comes with the
xserver-xorg-input-evdev package which I recompiled for Debian Stretch.

```
Option "SoftButtonAreas" "RBL RBR RBT RBB MBL MBR MBT MBB"
Option "SoftButtonAreas" "60% 0   0   40% 40% 60% 0   40%"
```
The acronyms in each 3 letter pair stand for:
`{Right|Middle}Button{Left|Right|Top|Bottom}`.

The configuration that I tried and ended up with is:

```
Option "SoftButtonAreas" "70% 0   0   20% 30% 70% 0   20%"
```

This corresponds to the following layout of the TouchPad. You can see
that the Left Button press extends downwards to the rest of the
TouchPad. Unfortunately, two finger scrolling won't work on the top 30%
area anymore.

```
   30%      40%     30%
+-------+--------+-------+
| Left  | Middle | Right | 30%
+       +--------+-------+
|                        |
|                        |
|                        | 70%
|                        |
|                        |
+------------------------+
```

[1]: https://aur.archlinux.org/packages/xf86-input-evdev-trackpoint/
[2]: https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=833919
[3]: http://askubuntu.com/a/443668/483416
