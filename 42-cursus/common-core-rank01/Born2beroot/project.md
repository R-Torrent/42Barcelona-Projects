# Born2beroot

Instructions for common-core-rank01/Born2beroot project, mandatory & *bonus* parts.

Operating system: Debian "Bookworm" v12.1<br>
Virtualization software: Oracle VM VirtualBox

**NOTES**:
- User throughout this file is `rtorrent`.
- Any other filename or such marked with a (§) can and should be adapted to the user's personal preferences.
- A text file with user, root, and partition passwords should be kept at hand.

---

## Installing & setting our virtual machine

[Download](https://cdimage.debian.org/debian-cd/current/amd64/iso-cd/debian-12.1.0-amd64-netinst.iso) the latest *stable* of Debian.

Open VirtualBox and select **`New`**.

### 1. VirtualBox Settings

#### Name and Operating System

> Name: `Born2beroot_Debian12.1.0` (§)<br>
> Folder: `cd /System/Volumes/Data/sgoinfre/Perso/rtorrent/` (§)
- Actual location of the `sgoinfre` folder may vary.
- User's folder in the public directory may be further protected: `chmod go-rwx rtorrent`
> ISO Image: Should be located in the `Downloads` folder.
- Further boxes should autofill.
> Skip Unattended Installation: ✓ this box

#### Hardware

> Base Memory: Leave as recommended, 2048 MB.<br>
> Processors: In my experience, OS installation will crash with more than 2 CPUs.

#### Hard Disk

> Create a Virtual Hard Disk Now: ☉ this button
- Hard Disk File location for the .vdi (VirtualBox Disk Image) should be automatically selected in our VM's folder.
- Increase size to 30.8 GB for the *bonus* sections of this project.
- No need to Pre-allocate Full Size.

After pressing **`Finish`**, the VM should be created in the `sgoinfre` subfolder of our choice.

**Start** the VM.
- At all times, one can switch from the host to the guest sytem, and back, by pressing the `⌘` key.

---

### 2. Installing Debian

**IMPORTANT: Immediately press the `↓` key in the keyboard to interrupt the *Graphic install* option. Select the *Install* option instead.**

Before continuing, resize the Machine's Window by pressing `⌘ + C`. Adjust the window to a comfortable size.

#### Select a language

> Language: `English - English`

#### Select your location

> Country, territory or area: `other` (§)<br>
> Continent or region: `Europe`<br>
> Country, territory or area: `Spain`

#### Configure locales

> Country to base default locale settings on: `United States - en_US.UTF-8`

#### Configure the keyboard

> Keymap to use: `American English`

#### Configure the network

> Hostname: `rtorrent42` (§)
- As per instructions, hostname **must** be the user's 42 login ending with 42.
> Domain name: ` ` \<leave empty\>

#### Set up users and passwords

> Root password: `Born2beroot00` (§)
- Remember to store this and all passwords in a safe location.
- Checking the `Show Password in Clear` option is very helpful.
> Full name for the new user: `Roger Torrent` (§)<br>
> Username for your account: `rtorrent` (§)
- As per instructions, an account with the user's 42 login **must** be present.
> Choose a password for the new user: `Born2berootrt` (§)

#### Configure the clock

> Select a location in your time zone: `Madrid` (§)

#### Partition disks

Set all partitions as: `Ext4 journaling file system`

> Partitioning method: `Manual`<br>
> `SCSI3 (0,0,0) (sda) - 33.1 GB ATA VBOX HARDDISK`
- Location for the new partition table.
> Create new empty partition table on this device? `Yes`
> `pri/log 33.1 GB FREE SPACE`<br>
> `Create a new partition`<br>
> New partition size: `500 MB`
- This will be `sda1` and contain the OS.
> Type for the new partition: `Primary`<br>
> Location for the new partition: `Beginning`<br>
> Partition settings:
>> Mount point: `/boot` \<After selecting `/boot - static files of the boot loader`\><br>
>> `Done setting up the partition`
> 
> `pri/log 32.6 GB FREE SPACE`<br>
> `Create a new partition`<br>
> New partition size: `max`
- Next create a LV (Logical Volume) with the rest of the free space.
> Type for the new partition: `Logical`<br>
> Partition settings:
>> Mount point: `none` \<After selecting `Do not mount it`\><br>
>> `Done setting up the partition`
>
> `Configure encrypted volumes`<br>
> Write the changes to disk and configure encrypted volumes? `Yes`<br>
> `Create encrypted volumes`<br>
> Devices to encrypt:
>> `[ ] /dev/sda1 (499MB; ext4)`<br>
>> `[*] /dev/sda5 (32569MB; ext4)`
- Encrypt only the logical volume.
> Partition settings:
>> `Done setting up the partition`<br>
>
> `Finish`<br>
> Really erase the data on SCSI3 (0,0,0), partition #5 (sda)? `Yes`
- It is safe to interrupt the installer as it overwrites partition #5; there is nothing to encrypt. Simply press `Cancel`.
> Encryption passphrase: `Born2beroot42` (§)
