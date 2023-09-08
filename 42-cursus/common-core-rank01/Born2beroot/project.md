# Born2beroot

Instructions for common-core-rank01/Born2beroot project, mandatory & *bonus* parts.

Operating system: Debian "Bookworm" v12.1.0<br>
Virtualization software: Oracle VM VirtualBox v7.0.8

**NOTES**:
- User throughout this file is `rtorrent`.
- Any other filename, password, or such marked with a (§) can and should be adapted to the user's personal preferences.
- A text file with user, root, and partition passwords should be kept at hand.

---

## A.- Installing & setting our virtual machine

[Download](https://cdimage.debian.org/debian-cd/current/amd64/iso-cd/debian-12.1.0-amd64-netinst.iso) the latest *stable* version of Debian.

Open VirtualBox and select **`New`**.

### 1. VirtualBox Settings

#### 1.a Name and Operating System

> Name: `Born2beroot_Debian12.1.0` (§)<br>
> Folder: `cd /System/Volumes/Data/sgoinfre/Perso/rtorrent/` (§)
- Actual location of the `sgoinfre` folder may vary.
- User's folder in the public directory may be further protected: `chmod go-rwx rtorrent`
> ISO Image: Should be located in the `Downloads` folder.
- Further boxes should autofill.
> `Skip Unattended Installation` ✓ this box

#### 1.b Hardware

> Base Memory: Leave as recommended, 2048 MB.<br>
> Processors: In my experience, OS installation at 42's facilities **will crash** with more than `1` CPU. We *may* choose to increase the number after the installation is complete.

#### 1.c Hard Disk

> `Create a Virtual Hard Disk Now` ☉ this button
- Hard Disk File location for the .vdi (VirtualBox Disk Image) should be automatically selected in our VM's folder.
- Increase size to `30.80 GB` for the *bonus* sections of this project. [**NOTE**: Both Debian and VirtualBox use the *traditional* 1 GB = (1,024)^3 = 1,073,741,824 bytes. However, Debian's installer uses the *modern* 1 GB = 1,000,000,000 bytes, perhaps to accomodate the manufacturers' scheming of inflated HD sizes.]
- No need to Pre-allocate Full Size.

After pressing **`Finish`**, the VM should be created in the `sgoinfre` subfolder of our choice.

**`Start`** the VM.
- At all times, one can switch from the host to the guest sytem, and back, by pressing the `⌘` key.

---

### 2. Installing Debian

**IMPORTANT: Immediately press the `↓` key in the keyboard to interrupt the *Graphic install* option. Select the *Install* option instead.**

Before continuing, resize the Machine's Window by pressing `⌘ + C`. Adjust the window to a comfortable size.

#### 2.a Select a language

> Language: `English - English`

#### 2.b Select your location

> Country, territory or area: `other` (§)<br>
> Continent or region: `Europe` (§)<br>
> Country, territory or area: `Spain` (§)

#### 2.c Configure locales

> Country to base default locale settings on: `United States - en_US.UTF-8`

#### 2.d Configure the keyboard

> Keymap to use: `American English`

#### 2.e Configure the network

> Hostname: `rtorrent42` (§)
- As per instructions, hostname **must** be the user's 42 login ending with 42.
> Domain name: ` ` \<leave empty\>

#### 2.f Set up users and passwords

> Root password: `Born2beroot00` (§)<br>
> Re-enter password to verify: `Born2beroot00` (§)
- Remember to store this and all passwords in a safe location.
- Checking the `Show Password in Clear` option is very helpful.
> Full name for the new user: `Roger Torrent` (§)<br>
> Username for your account: `rtorrent` (§)
- As per instructions, an account with the user's 42 login **must** be present.
> Choose a password for the new user: `Born2berootrt` (§)<br>
> Re-enter password to verify: `Born2berootrt` (§)

#### 2.d Configure the clock

> Select a location in your time zone: `Madrid` (§)

#### 2.e Partition disks

> Partitioning method: `Manual`<br>
> `SCSI3 (0,0,0) (sda) - 33.1 GB ATA VBOX HARDDISK`
- Location for the new partition table. [NOTE: The installer may revert to the SCSI1 or SCSI2 protocols. Don't worry about this.]
> Create new empty partition table on this device? `Yes`<br>
> `pri/log 33.1 GB FREE SPACE`<br>
> How to use this free space: `Create a new partition`<br>
> New partition size: `525`
- This will be `sda1` and contain the OS.
> Type for the new partition: `Primary`<br>
> Location for the new partition: `Beginning`<br>
> Partition settings:
>> Mount point: `/boot` \<After selecting `/boot - static files of the boot loader`\><br>
>> `Done setting up the partition`
> 
> `pri/log 32.5 GB FREE SPACE`<br>
> How to use this free space: `Create a new partition`<br>
> New partition size: `max`
- Next create a LV (Logical Volume) with the rest of the free space.
> Type for the new partition: `Logical`<br>
> Partition settings:
>> Mount point: `none` \<After selecting `Do not mount it`\><br>
>> `Done setting up the partition`
>
> `Configure encrypted volumes`<br>
> Write the changes to disk and configure encrypted volumes? `Yes`<br>
> Encryption configuration actions: `Create encrypted volumes`<br>
> Devices to encrypt:
>> `[ ] /dev/sda1 (524MB; ext4)`<br>
>> `[*] /dev/sda5 (32544MB; ext4)`
- Encrypt only the logical volume.
> Partition settings:
>> `Done setting up the partition`
>
> Encryption configuration actions: `Finish`<br>
> Really erase the data on SCSI3 (0,0,0), partition #5 (sda)? `No`
- Should `Yes` be selected, interrupt the installer by pressing `Cancel` as it overwrites partition #5; it is safe, as there is nothing to encrypt.
> Encryption passphrase: `Born2beroot42` (§)<br>
> Re-enter passphrase to verify: `Born2beroot42` (§)<br>
> `Configure the Logical Volume Manager`<br>
> Write the changes to disks and configure LVM? `Yes`<br>
> LVM configuration action: `Create volume group`
- Selecting `Display configuration details` at this stage of the installation will show the progress of the configuration as new volumes are included into the group.
> Volume group name: `LVMGroup`
- This is the name suggested in the project's document.
> Devices for the new volume group:
>> `[*] /dev/mapper/sda5_crypt (32527MB; ext4)`<br>
>> `[ ] /dev/sda1 (524MB; ext4)`
>
> LVM configuration action: `Create logical volume`<br>
> Volume group: `LVMGroup (32526MB)`<br>
> Logical volume name: `root`<br>
> Logical volume size: `10737`
- And repeat for the next six volumes in the group!
> LVM configuration action: `Create logical volume`<br>
> Volume group: `LVMGroup (21793MB)`<br>
> Logical volume name: `swap`<br>
> Logical volume size: `2470`<br>
> LVM configuration action: `Create logical volume`<br>
> Volume group: `LVMGroup (19327MB)`<br>
> Logical volume name: `home`<br>
> Logical volume size: `5369`<br>
> LVM configuration action: `Create logical volume`<br>
> Volume group: `LVMGroup (13958MB)`<br>
> Logical volume name: `var`<br>
> Logical volume size: `3221`<br>
> LVM configuration action: `Create logical volume`<br>
> Volume group: `LVMGroup (10741MB)`<br>
> Logical volume name: `srv`<br>
> Logical volume size: `3221`<br>
> LVM configuration action: `Create logical volume`<br>
> Volume group: `LVMGroup (7524MB)`<br>
> Logical volume name: `tmp`<br>
> Logical volume size: `3221`<br>
> LVM configuration action: `Create logical volume`<br>
> Volume group: `LVMGroup (4307MB)`<br>
> Logical volume name: `var-log`<br>
> Logical volume size: `4307MB` \<leave unchanged\><br>
> LVM configuration action: `Finish`
- We now have to specify the use and mounting points for each of the volumes in the group:
>> `LVM VG LVMGroup, LV home - 5.4 GB Linux device-mapper (linear)`<br>
>> `#1 5.4 GB` \<select this row\>
>
> Partition settings:
>> Use as: `Ext4 journaling file system`<br>
>> Mount point: `/home` \<After selecting `/home - user home directories`\><br>
>> `Done setting up the partition`
>
>> `LVM VG LVMGroup, LV root - 10.7 GB Linux device-mapper (linear)`<br>
>> `#1 10.7 GB` \<select this row\>
>
> Partition settings:
>> Use as: `Ext4 journaling file system`<br>
>> Mount point: `/` \<After selecting `/ - the root file system`\><br>
>> `Done setting up the partition`
>
>> `LVM VG LVMGroup, LV srv - 3.2 GB Linux device-mapper (linear)`<br>
>> `#1 3.2 GB` \<select this row\>
>
> Partition settings:
>> Use as: `Ext4 journaling file system`<br>
>> Mount point: `/srv` \<After selecting `/srv - data for services provided by this system`\><br>
>> `Done setting up the partition`
>
>> `LVM VG LVMGroup, LV swap - 2.5 GB Linux device-mapper (linear)`<br>
>> `#1 2.5 GB` \<select this row\>
>
> Partition settings:
>> Use as: `swap area`
- This partition does not use the Ext4 file system. No mount point required either.
>> `Done setting up the partition`
>
>> `LVM VG LVMGroup, LV tmp - 3.2 GB Linux device-mapper (linear)`<br>
>> `#1 3.2 GB` \<select this row\>
>
> Partition settings:
>> Use as: `Ext4 journaling file system`<br>
>> Mount point: `/tmp` \<After selecting `/tmp - temporary files`\><br>
>> `Done setting up the partition`
>
>> `LVM VG LVMGroup, LV var - 3.2 GB Linux device-mapper (linear)`<br>
>> `#1 3.2 GB` \<select this row\>
>
> Partition settings:
>> Use as: `Ext4 journaling file system`<br>
>> Mount point: `/var` \<After selecting `/var - variable data`\><br>
>> `Done setting up the partition`
>
>> `LVM VG LVMGroup, LV var-log - 4.3 GB Linux device-mapper (linear)`<br>
>> `#1 4.3 GB` \<select this row\>
>
> Partition settings:
>> Use as: `Ext4 journaling file system`<br>
>> Mount point: `/var/log` \<After selecting `Enter manually` and typing `/var/log`\><br>
>> `Done setting up the partition`
>
> `Finish partitioning and write changes to disk`<br>

![Partition disks overview](src/img1.png "Your screen should look similar to this!")

> Write the changes to disks? `Yes`

#### 2.f Install the base system

Installation of the OS at this stage may take a while.

#### 2.g Configure the package manager

> Scan extra installation media? `No`<br>
> Debian archive mirror country: `Spain` (§)<br>
> Debian archive mirror: `deb.debian.org`<br>
> HTTP proxy information (blank for none): ` ` \<leave empty\>

#### 2.h Configuring popularity-contest

> Participate in the package usage survey? `No`

#### 2.i Software selection

> Choose software to install:
>> `[ ] Debian desktop environment`<br>
>> `[ ] ... GNOME`<br>
>> `[ ] ... Xfce`<br>
>> `[ ] ... GNOME Flashback`<br>
>> `[ ] ... KDE Plasma`<br>
>> `[ ] ... Cinnamon`<br>
>> `[ ] ... MATE`<br>
>> `[ ] ... LXDE`<br>
>> `[ ] ... LXQt`<br>
>> `[ ] web server`<br>
>> `[*] SSH server`<br>
>> `[*] standard system utilities`
- Deselect all preselected options except for the last, and install the predefined SSH collection (OpenSSH). The `standard system utilities` option gives us access to the **man** pages of the commands.

#### 2.j Configuring grub-pc

> Install the GRUB boot loader to your primary drive? `Yes`<br>
> Device for boot loader installation: `/dev/sda (ata-VBOX_HARDDISK_VB6f2eb40c-0d001e88)`
- Obviously, the serial number above will be different in each case.

#### 2.k Finish the installation

> `Continue`
- Success! [**TIP**: Cloning the virtual machine after the installation is a sensible precaution before moving on.]

---

### 3. Configuring the virtual machine

Henceforth, enter your Debian installation by pressing `Debian GNU/Linux` in the GNU GRUB loading screen, and unlock the encrypted partition:
> Please unlock disk sda5_crypt: `Born2beroot42` (§)

But before continuing, power the machine off to enable the ports.

#### 3.a Setting the ports

Navigate to the `Network` menu, either by pressing the **`Settings`** button or the `Network` reticule of the machine's `Display` view.<br>
Expand to the `Advanced` options and press the **`Port Forwarding`** button.

![Port Forwarding](src/img2.png "Press the 'Port Forwarding' button")

Add a new rule (green button in the top right corner):
> `Name     Protocol    Host Port   Guest Port`<br>
> `Rule 1   TCP         1717        4242      `
- *Host port* may be any port of our liking, `1717` (§) in this case, but it **must** be rerouted to *guest port* `4242` in our virtual machine.

Turn the machine on  and login as `root` user to continue with the project:
> rtorrent42 login: `root` (§)<br>
> Password: `Born2beroot00` (§)

#### 3.b Secure Shell setup

A SSH server should be present in the machine from the software selection phase of the OS installation. You may test this with `service ssh status`. If this is not the case, install it now by typing `apt install openssh-server` and confirm with `y`.

Configure the daemon to suit the document's specifications. Open the main configuration file `/etc/ssh/sshd_config` with your preferred text editor:
> `vi /etc/ssh/sshd_config` (§)
- Observe that there is also a `ssh_config` file, a `ssh_config.d` folder, and a `sshd_config.d` folder in `/etc/ssh/`. Check your spelling!
- The config file basically consists of an `Include` directive to call further config files stored in the `sshd_config.d` folder, and a list of *commented out* settings (starting with the `#` character). These are the default settings the server runs on.

Uncomment `Port` selection in line 14, modifying the default port 22 **sshd** listens on:
> `Port 4242`

Uncomment `PermitRootLogin` selection in line 33 as, per instructions, "it must not be possible to connect using SSH as root".
> `PermitRootLogin no`
- Open the man page for further details, `man sshd_config`. Again, the manual should be present in the system from the software selection phase. Should the package be missing, you may install it with `apt install man-db`. Confirm with `y`.

Restart the service to force the changes:
> `service ssh restart`
- Check with `service ssh status` that the listened port has indeed changed to 4242.

**ssh_config** configures the SSH client one uses to SSH *another* machine. **sshd_config** configures the daemon that listens to any incoming connection request to the SSH port. The document does not mandate us to set a client in the virtual machine.

#### 3.c Uncomplicated Firewall setup

> `apt install ufw`<br>
> Do you want to continue? [Y/n] `⏎` \<a simple `y` in the keyboard would also suffice\><br>
> `ufw enable`
- Activates UFW for immediate use and enables it on system boot.
> `ufw allow 4242`
- As instructed in the document, port 4242 is left open.
- Type `ufw status` to confirm that port 4242 is indeed open.
