# Born2beroot

Instructions for common-core-rank01/Born2beroot project, mandatory & *bonus* parts.

Operating system: Debian "Bookworm" v12.1.0<br>
Virtualization software: Oracle VM VirtualBox v7.0.8

**NOTES**:
- User throughout this file is `rtorrent`.
- Any other filename, password, or such marked with a (§) can and should be adapted to the user's personal preferences.
- A text file with user, root, and partition passwords should be kept at hand.

---

## Installing & setting our virtual machine

[Download](https://cdimage.debian.org/debian-cd/current/amd64/iso-cd/debian-12.1.0-amd64-netinst.iso) the latest *stable* version of Debian.

Open VirtualBox and select **`New`**.

### 1. VirtualBox Settings

#### Name and Operating System

> Name: `Born2beroot_Debian12.1.0` (§)<br>
> Folder: `cd /System/Volumes/Data/sgoinfre/Perso/rtorrent/` (§)
- Actual location of the `sgoinfre` folder may vary.
- User's folder in the public directory may be further protected: `chmod go-rwx rtorrent`
> ISO Image: Should be located in the `Downloads` folder.
- Further boxes should autofill.
> `Skip Unattended Installation` ✓ this box

#### Hardware

> Base Memory: Leave as recommended, 2048 MB.<br>
> Processors: In my experience, OS installation at 42's facilities will crash with more than `2` CPUs.

#### Hard Disk

> `Create a Virtual Hard Disk Now` ☉ this button
- Hard Disk File location for the .vdi (VirtualBox Disk Image) should be automatically selected in our VM's folder.
- Increase size to `28.70 GB` for the *bonus* sections of this project. NOTE: VirtualBox uses the *traditional* 1 GB = 1,073,741,824 bytes, while Debian's installer uses the *modern* 1 GB = 1,000,000,000 bytes. These 28.70 GB correspond with the 30.8 GB of the project's document.
- No need to Pre-allocate Full Size.

After pressing **`Finish`**, the VM should be created in the `sgoinfre` subfolder of our choice.

**`Start`** the VM.
- At all times, one can switch from the host to the guest sytem, and back, by pressing the `⌘` key.

---

### 2. Installing Debian

**IMPORTANT: Immediately press the `↓` key in the keyboard to interrupt the *Graphic install* option. Select the *Install* option instead.**

Before continuing, resize the Machine's Window by pressing `⌘ + C`. Adjust the window to a comfortable size.

#### Select a language

> Language: `English - English`

#### Select your location

> Country, territory or area: `other` (§)<br>
> Continent or region: `Europe` (§)<br>
> Country, territory or area: `Spain` (§)

#### Configure locales

> Country to base default locale settings on: `United States - en_US.UTF-8`

#### Configure the keyboard

> Keymap to use: `American English`

#### Configure the network

> Hostname: `rtorrent42` (§)
- As per instructions, hostname **must** be the user's 42 login ending with 42.
> Domain name: ` ` \<leave empty\>

#### Set up users and passwords

> Root password: `Born2beroot00` (§)<br>
> Re-enter password to verify: `Born2beroot00` (§)
- Remember to store this and all passwords in a safe location.
- Checking the `Show Password in Clear` option is very helpful.
> Full name for the new user: `Roger Torrent` (§)<br>
> Username for your account: `rtorrent` (§)
- As per instructions, an account with the user's 42 login **must** be present.
> Choose a password for the new user: `Born2berootrt` (§)<br>
> Re-enter password to verify: `Born2berootrt` (§)

#### Configure the clock

> Select a location in your time zone: `Madrid` (§)

#### Partition disks

Set all partitions as: `Ext4 journaling file system`

> Partitioning method: `Manual`<br>
> `SCSI3 (0,0,0) (sda) - 30.8 GB ATA VBOX HARDDISK`
- Location for the new partition table.
> Create new empty partition table on this device? `Yes`<br>
> `pri/log 30.8 GB FREE SPACE`<br>
> How to use this free space: `Create a new partition`<br>
> New partition size: `500M`
- This will be `sda1` and contain the OS.
> Type for the new partition: `Primary`<br>
> Location for the new partition: `Beginning`<br>
> Partition settings:
>> Mount point: `/boot` \<After selecting `/boot - static files of the boot loader`\><br>
>> `Done setting up the partition`
> 
> `pri/log 30.3 GB FREE SPACE`<br>
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
>> `[ ] /dev/sda1 (499MB; ext4)`<br>
>> `[*] /dev/sda5 (30314MB; ext4)`
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
>> `[*] /dev/mapper/sda5_crypt (30297MB; ext4)`<br>
>> `[ ] /dev/sda1 (499MB; ext4)`
>
> LVM configuration action: `Create logical volume`<br>
> Volume group: `LVMGroup (30295MB)`<br>
> Logical volume name: `root`<br>
> Logical volume size: `10G`
- And repeat for the next six volumes in the group!
> LVM configuration action: `Create logical volume`<br>
> Volume group: `LVMGroup (20296MB)`<br>
> Logical volume name: `swap`<br>
> Logical volume size: `2.3G`<br>
> LVM configuration action: `Create logical volume`<br>
> Volume group: `LVMGroup (17997MB)`<br>
> Logical volume name: `home`<br>
> Logical volume size: `5G`<br>
> LVM configuration action: `Create logical volume`<br>
> Volume group: `LVMGroup (12998MB)`<br>
> Logical volume name: `var`<br>
> Logical volume size: `3G`<br>
> LVM configuration action: `Create logical volume`<br>
> Volume group: `LVMGroup (9999MB)`<br>
> Logical volume name: `srv`<br>
> Logical volume size: `3G`<br>
> LVM configuration action: `Create logical volume`<br>
> Volume group: `LVMGroup (7000MB)`<br>
> Logical volume name: `tmp`<br>
> Logical volume size: `3G`<br>
> LVM configuration action: `Create logical volume`<br>
> Volume group: `LVMGroup (4001MB)`<br>
> Logical volume name: `var-log`<br>
> Logical volume size: `4001MB`<br>
> LVM configuration action: `Finish`
- We now have to specify the use and mounting points for each of the volumes in the group:
>> `LVM VG LVMGroup, LV home - 5.0 GB Linux device-mapper (linear)`<br>
>> `#1 5.0 GB` \<select this row\>
>
> Partition settings:
>> Use as: `Ext4 journaling file system`<br>
>> Mount point: `/home` \<After selecting `/home - user home directories`\><br>
>> `Done setting up the partition`
>
>> `LVM VG LVMGroup, LV root - 10.0 GB Linux device-mapper (linear)`<br>
>> `#1 10.0 GB` \<select this row\>
>
> Partition settings:
>> Use as: `Ext4 journaling file system`<br>
>> Mount point: `/` \<After selecting `/ - the root file system`\><br>
>> `Done setting up the partition`
>
>> `LVM VG LVMGroup, LV srv - 3.0 GB Linux device-mapper (linear)`<br>
>> `#1 3.0 GB` \<select this row\>
>
> Partition settings:
>> Use as: `Ext4 journaling file system`<br>
>> Mount point: `/srv` \<After selecting `/srv - data for services provided by this system`\><br>
>> `Done setting up the partition`
>
>> `LVM VG LVMGroup, LV swap - 2.3 GB Linux device-mapper (linear)`<br>
>> `#1 2.3 GB` \<select this row\>
>
> Partition settings:
>> Use as: `swap area`
- This partition does not use the Ext4 file system. No mount point required either.
>> `Done setting up the partition`
>
>> `LVM VG LVMGroup, LV tmp - 3.0 GB Linux device-mapper (linear)`<br>
>> `#1 3.0 GB` \<select this row\>
>
> Partition settings:
>> Use as: `Ext4 journaling file system`<br>
>> Mount point: `/tmp` \<After selecting `/tmp - temporary files`\><br>
>> `Done setting up the partition`
>
>> `LVM VG LVMGroup, LV var - 3.0 GB Linux device-mapper (linear)`<br>
>> `#1 3.0 GB` \<select this row\>
>
> Partition settings:
>> Use as: `Ext4 journaling file system`<br>
>> Mount point: `/var` \<After selecting `/var - variable data`\><br>
>> `Done setting up the partition`
>
>> `LVM VG LVMGroup, LV var-log - 4.0 GB Linux device-mapper (linear)`<br>
>> `#1 4.0 GB` \<select this row\>
>
> Partition settings:
>> Use as: `Ext4 journaling file system`<br>
>> Mount point: `/var/log` \<After selecting `Enter manually` and typing `/var/log`\><br>
>> `Done setting up the partition`
>
> `Finish partitioning and write changes to disk`<br>
> Write the changes to disks? `Yes`

#### Install the base system

This stage may take a while. Sadly, it is prone to error.
