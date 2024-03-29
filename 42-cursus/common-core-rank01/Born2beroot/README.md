# Born2beroot

**Guide to solve `common-core-rank01/Born2beroot` (version 2) project, *mandatory* & *bonus* parts.**

Operating system: **Debian "Bookworm" v12.1.0**<br>
Virtualization software: **Oracle VM VirtualBox v7.0.8**

**NOTES**:
- User login throughout this file is `rtorrent`.
- Any login, filename, password, or such marked with a (§) can and ***should*** be adapted to the user's personal preferences.
- A text file with user, root, and partition passwords should be kept at hand.
- Popular text editors available with the bare Debian build are **vi** and **nano**. **Emacs** requires an installation (`apt install emacs`) first. Commands in this tutorial reliant on the choice of a text editor are marked with (†).
- On November 22, 2023, the **VirtualBox** *hypervisor* was uninstalled from the 42Barcelona server, following unspecified "technical issues" allegations. It was replaced with **VMware Fusion** for an undefined period of time, meaning this guide is obsolete *even before its author has presented his project for evaluation*! It goes without saying that I ***shall not*** redo this document. I have found that nothing of real significance (for this project) changes, although I admit to a very short experience with the new application, but I suggest to un-**✓** the `Split into multiple files` advanced option in the **`Hard Disk (SCSI)`** settings to simplify step **§ A.6 The final signature**. Not that `shasum *.vmdk > signature.txt` for multiple files is in itself particularly complicated…

---

## A. Installing our virtual machine & setting the server

[Download](https://cdimage.debian.org/debian-cd/current/amd64/iso-cd/) the latest *stable* version of Debian. Currently, this will be image `debian-12.1.0-amd64-netinst.iso`.

Open VirtualBox and select **`New`**.

- You may determine your VirtualBox release version by executing in the CLI
> VBoxManage -v

---

### A.1 VirtualBox Settings

#### A.1.a Name and Operating System

> Name: `Born2beroot_Debian12.1.0` (§)<br>
> Folder: `cd /System/Volumes/Data/sgoinfre/Perso/rtorrent/` (§)
- Actual location of the `SGoinfre` folder in the 42 system might vary. A symbolic link in the root directory, `/sgoinfre`, is probably present.
- User's folder in the public directory may be further protected: `chmod go-rwx rtorrent` (§). Check the local rules governing `SGoinfre` in the `F.A.Q.` link of the *intra*.
> ISO Image: Probably located in the student's `Downloads` folder.
- Further boxes will autofill.
> `Skip Unattended Installation` **✓** this box

#### A.1.b Hardware

> Base Memory: Leave as recommended, 2048 MB.<br>
> Processors: In my experience, OS installation at 42's facilities ***will crash*** with more than `1` CPU selected. We *may* choose to increase the number after the installation is complete.

#### A.1.c Hard Disk

> `Create a Virtual Hard Disk Now` **☉** this button
- Hard Disk File location for the `.vdi` (VirtualBox Disk Image) should be automatically selected in our VM's folder.
- Increase size to `30.80 GB` for the *bonus* sections of this project.<br>
  [**NOTE**: Both Debian and VirtualBox use the *traditional* 1 GB = (1,024)^3 = 1,073,741,824 bytes. However, Debian's installer uses the *modern* 1 GB = 1,000,000,000 bytes, perhaps to accomodate hardware manufacturers' scheming of inflated HD sizes.]
- Do not *Pre-allocate Full Size*, as you will exceed your assigned space quota in disk.

After pressing **`Finish`**, the VM should be created in the `sgoinfre` subfolder of our choosing.

**`Start`** the VM.
- At all times, one can switch from the host to the guest sytem, and back, by pressing the `⌘` key.

---

### A.2 Installing Debian

**IMPORTANT: Immediately press the `↓` key in the keyboard to interrupt the *Graphic install* option. Select the *Install* option instead.**

Before continuing, resize the Machine's Window by pressing `⌘ + C`. Use the mouse to adjust the window to a comfortable size.

#### A.2.a Select a language

> Language: `English - English`

#### A.2.b Select your location

> Country, territory or area: `other` (§)<br>
> Continent or region: `Europe` (§)<br>
> Country, territory or area: `Spain` (§)

#### A.2.c Configure locales

> Country to base default locale settings on: `United States - en_US.UTF-8`

#### A.2.d Configure the keyboard

> Keymap to use: `American English`

#### A.2.e Configure the network

> Hostname: `rtorrent42` (§)
- As per instructions, hostname ***must*** be the user's 42 login ending with 42.
> Domain name: ` ` \<leave empty\>

#### A.2.f Set up users and passwords

> Root password: `Born2berude` (§)<br>
> Re-enter password to verify: `Born2berude` (§)
- Remember to store this and all passwords in a safe location.
- Root password should comply with all the restrictions listed in the `.pdf` document.
- Checking the `Show Password in Clear` option is very helpful. Use the space bar to mark particular options while using the install interface.
> Full name for the new user: `Roger Torrent` (§)<br>
> Username for your account: `rtorrent` (§)
- As per instructions, an account with the user's 42 login ***must*** be present.
> Choose a password for the new user: `Born2becute` (§)<br>
> Re-enter password to verify: `Born2becute` (§)
- Again, comply with the password policy.

#### A.2.g Configure the clock

> Select a location in your time zone: `Madrid` (§)

#### A.2.h Partition disks

> Partitioning method: `Manual`<br>
> `SCSI3 (0,0,0) (sda) - 33.1 GB ATA VBOX HARDDISK`
- Location for the new partition table.<br>
[**NOTE**: The installer may revert to the SCSI1 or SCSI2 protocols. Don't fret over this.]
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

Next, create a LV (Logical Volume) with the rest of the free space.
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
- Should `Yes` be selected, interrupt the installer by pressing `Cancel` as it scrambles partition #5; it is perfectly safe, as there was nothing there to hide.
> Encryption passphrase: `Born2beroot` (§)<br>
> Re-enter passphrase to verify: `Born2beroot` (§)<br>
> `Configure the Logical Volume Manager`<br>
> Write the changes to disks and configure LVM? `Yes`<br>
> LVM configuration action: `Create volume group`
- Selecting `Display configuration details` at any point of this stage of the installation will show the progress of the configuration as new volumes are included into the group. Use this display to check your progress if you lose track of the endeavour.
> Volume group name: `LVMGroup`
- This is the name suggested in the project's document.
> Devices for the new volume group:
>> `[*] /dev/mapper/sda5_crypt (32527MB; ext4)`<br>
>> `[ ] /dev/sda1 (524MB; ext4)`

Create the seven encrypted partitions with LVM:
> LVM configuration action: `Create logical volume`<br>
> Volume group: `LVMGroup (32526MB)`<br>
> Logical volume name: `root`<br>
> Logical volume size: `10737`

And repeat for the next six volumes in the group!
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

We now have to specify the use and mounting points for each of the volumes in the group:
>> `LVM VG LVMGroup, LV home - 5.4 GB Linux device-mapper (linear)`<br>
>> `#1 5.4 GB` \<select this row\>
>
> Partition settings:
>> Use as: `Ext4 journaling file system`<br>
>> Mount point: `/home` \<After selecting `/home - user home directories`\><br>
>> `Done setting up the partition`

>> `LVM VG LVMGroup, LV root - 10.7 GB Linux device-mapper (linear)`<br>
>> `#1 10.7 GB` \<select this row\>
>
> Partition settings:
>> Use as: `Ext4 journaling file system`<br>
>> Mount point: `/` \<After selecting `/ - the root file system`\><br>
>> `Done setting up the partition`

>> `LVM VG LVMGroup, LV srv - 3.2 GB Linux device-mapper (linear)`<br>
>> `#1 3.2 GB` \<select this row\>
>
> Partition settings:
>> Use as: `Ext4 journaling file system`<br>
>> Mount point: `/srv` \<After selecting `/srv - data for services provided by this system`\><br>
>> `Done setting up the partition`

>> `LVM VG LVMGroup, LV swap - 2.5 GB Linux device-mapper (linear)`<br>
>> `#1 2.5 GB` \<select this row\>
>
> Partition settings:
>> Use as: `swap area`
- This partition does not use the Ext4 file system. No mount point required either. The *swap area* is the space where inactive memory pages are stored when the physical RAM memory runs out.
>> `Done setting up the partition`

>> `LVM VG LVMGroup, LV tmp - 3.2 GB Linux device-mapper (linear)`<br>
>> `#1 3.2 GB` \<select this row\>
>
> Partition settings:
>> Use as: `Ext4 journaling file system`<br>
>> Mount point: `/tmp` \<After selecting `/tmp - temporary files`\><br>
>> `Done setting up the partition`

>> `LVM VG LVMGroup, LV var - 3.2 GB Linux device-mapper (linear)`<br>
>> `#1 3.2 GB` \<select this row\>
>
> Partition settings:
>> Use as: `Ext4 journaling file system`<br>
>> Mount point: `/var` \<After selecting `/var - variable data`\><br>
>> `Done setting up the partition`

>> `LVM VG LVMGroup, LV var-log - 4.3 GB Linux device-mapper (linear)`<br>
>> `#1 4.3 GB` \<select this row\>
>
> Partition settings:
>> Use as: `Ext4 journaling file system`<br>
>> Mount point: `/var/log` \<After selecting `Enter manually` and typing `/var/log`\><br>
>> `Done setting up the partition`

> `Finish partitioning and write changes to disk`

![Partition disks overview](src/img00.png "Your screen should look like this!")

> Write the changes to disks? `Yes`

#### A.2.i Installing the base system

Installation of the OS at this stage may take a while.

#### A.2.j Configure the package manager

> Scan extra installation media? `No`<br>
> Debian archive mirror country: `Spain` (§)<br>
> Debian archive mirror: `deb.debian.org`<br>
> HTTP proxy information (blank for none): ` ` \<leave empty\>

#### A.2.k Configuring popularity-contest

> Participate in the package usage survey? `No`

#### A.2.l Software selection

> Choose software to install:
>> `[ ] Debian desktop environment`<br>
>> `[ ] ... GNOME                 `<br>
>> `[ ] ... Xfce                  `<br>
>> `[ ] ... GNOME Flashback       `<br>
>> `[ ] ... KDE Plasma            `<br>
>> `[ ] ... Cinnamon              `<br>
>> `[ ] ... MATE                  `<br>
>> `[ ] ... LXDE                  `<br>
>> `[ ] ... LXQt                  `<br>
>> `[ ] web server                `<br>
>> `[*] SSH server                `<br>
>> `[*] standard system utilities `
- Deselect all preselected options except for the last, and install the predefined SSH collection (OpenSSH). The `standard system utilities` option gives us access to the **man** pages of the commands.<br>
  Alternatively, just deselect everything; later on you may install the precise packages yourself.

#### A.2.m Configuring grub-pc

GNU GRand Unified Bootloader, GRUB, is a boot loader for the Linux system that allows a user the choice to boot one of multiple operating systems installed on a computer or select a specific kernel configuration available on a particular operating system's partitions.
> Install the GRUB boot loader to your primary drive? `Yes`<br>
> Device for boot loader installation: `/dev/sda (ata-VBOX_HARDDISK_VB6f2eb40c-0d001e88)`
- Obviously, the disk model and identifier above will be different in each case.

#### A.2.n Finish the installation

> `Continue`

Success!<br>
[**TIP**: Cloning the virtual machine after this lengthy installation is a sensible precaution before moving on.]

---

### A.3 Configuring the virtual machine

Henceforth, enter your Debian installation by pressing `Debian GNU/Linux` in the GNU GRUB loading screen, and unlock the encrypted partition:
> Please unlock disk sda5_crypt: `Born2beroot42` (§)

But before continuing, power the machine off and enable the ports.

#### A.3.a Setting the ports

Navigate to the `Network` menu, either by pressing the **`Settings`** button or the `Network` reticule of the machine's `Display` view.<br>
Expand to the `Advanced` options and press the **`Port Forwarding`** button.

![Port Forwarding](src/img01.png "Press the 'Port Forwarding' button")

Add a new rule (green button in the top right corner):
> `Name     Protocol    Host Port   Guest Port`<br>
> `Rule 1   TCP         1717        4242      ` (§)
- *Host port* may be any port of our liking, `1717` (§) in this case, but it ***must*** be rerouted to *guest port* `4242` in our virtual machine.
- This rerouting is not strictly necessary, as will be readily seen in **§ B.5.g SSH**, but it simplifies things.

Turn the machine on and login as `root` user to continue with the project:
> rtorrent42 login: `root` (§)<br>
> Password: `Born2becute` (§)

#### A.3.b Secure Shell setup

A SSH server should be present in the machine from the software selection phase of the OS installation. You may test this with `service ssh status`. If this is not the case, install it now by typing `apt install openssh-server` and confirm with `y`.

Next, configure the daemon to suit the document's specifications. Open the main configuration file `/etc/ssh/sshd_config` with your preferred text editor, **vi** in my case:
> vi /etc/ssh/sshd_config (†)
- Observe that there is also a **ssh_config** file, a **ssh_config.d** folder, and a **sshd_config.d** folder in `/etc/ssh/`. Check your spelling!
- The config file basically consists of an `Include` directive to call further config files stored in the **sshd_config.d** folder, and a list of *commented out* settings (starting with the `#` character). These are the default settings the server runs on.

Uncomment `Port` selection in line 14, modifying the default port 22 **sshd** listens on:

	Port 4242

Uncomment `PermitRootLogin` selection in line 33 as, per instructions, "it must not be possible to connect using SSH as root":

	PermitRootLogin no
- Open the **man** page for further details, `man 5 sshd_config`. Again, the manual should be present in the system from the software selection phase. Should the package be missing, you may install it with `apt install man-db`. Confirm with `y`.

Restart the service to force the changes:
> service ssh restart
- Check with `service ssh status` that the listened port has indeed changed to 4242.

![**service ssh status** output](src/img04.png "Observe that sshd listens to port 4242")

**sshd_config** configures the daemon that listens to any incoming connection request to the SSH port. By contrast, **ssh_config** configures the SSH client one uses to SSH *another* machine. The document does not mandate us to set this client in the virtual machine, and so we shan't tinker any further!

#### A.3.c Uncomplicated Firewall setup
> apt install ufw<br>
> Do you want to continue? [Y/n] `y` \<a simple `⏎` in the keyboard would also suffice\>

Activate UFW for immediate use and enable it on system boot:
> ufw enable

As instructed in the document, port `4242` is left open:
> ufw allow 4242
- Confirm this is indeed the case with `ufw status`.
- Check the **man** page if needed, `man 8 ufw`.

![**ufw status** output](src/img05.png "Port 4242 open to IPv4 & IPv6 traffic")

#### A.3.d Strong password policy

Open the configuration file that stores user account parameters, `/etc/login.defs`, with your preferred text editor:
> vi /etc/login.defs (†)

Find definition `PASS_MAX_DAYS` and edit from `99999` to the mandated `30`.<br>
Find definition `PASS_MIN_DAYS` and edit from `0` to `2`.<br>
Seven-day warning to password expiration (`PASS_WARN_AGE`) is correctly set to `7` by default.

	#
	# Password aging controls:
	#
	#       PASS_MAX_DAYS   Maximum number of days a password may be used.
	#       PASS_MIN_DAYS   Minimum number of days allowed between password changes.
	#       PASS_WARN_AGE   Number of days warning given before a password expires.
	#
	PASS_MAX_DAYS   30
	PASS_MIN_DAYS   2
	PASS_WARN_AGE   7
- In addition to password aging controls, the file directs other parameters, such as mailbox location and the password encryption method.
- This file is accessed by commands such as **useradd** and **groupadd**.
- Account aging information can be checked and edited for specific users with **chage**. There's a use for it in **§ B.5.c User**.
- Open the **man** pages for further details, `man 5 login.defs` and `man 1 chage`.

Some of the options in **login.defs** are obsolete and are handled by PAM (Pluggable Authentication Modules). So let us install the required PAM password management module next:
> apt -y install libpam-pwquality
- `-y` option spares us the confirmation request after the **apt** command.
- You may check if the package is installed with `dpkg -s libpam-pwquality`.

Password policies are defined in `/etc/pam.d/common-password`. Edit the file:
> vi /etc/pam.d/common-password (†)

Locate line 25:

	password   requisite   pam_pwquality.so retry=3

Column 1, `password`, is the management group for the service, *Password group* in our case. Other groups we may find are *Auth*, *Account*, and *Session groups*.<br>
Column 2, `requisite`, is the *Control flag* in the service file. *Requisite* is the strongest flag. Should the requisite not be found or fails to load, it will stop loading other modules and return failure.<br>
Column 3, `pam_pwquality.so`, is the *Module* (.so file) used.<br>
Column 4, `retry=3`, contains *Module parameters*. The document does not specify a number of retries—the default value is `1`—, so replace this parameter with the specified requirements:

	password   requisite   pam_pwquality.so minlen=10 ucredit=-1 lcredit=-1 dcredit=-1 maxrepeat=3 reject_username difok=7 enforce_for_root
- All parameters should go in the same *line*, that is, before a newline character.

`minlen=10`: minimum acceptable size.<br>
`ucredit=-1`: minimum number of upper case letters. (‡)<br>
`lcredit=-1`: minumum number of lower case letters. (‡)<br>
`dcredit=-1`: minimum number of digits. (‡)<br>
`maxrepeat=3`: limit on repeated consecutive characters.<br>
`reject_username`: rejects the new password if it contains the login, either in straight or reversed form.<br>
`difok=7`: number of changes (inserts, removals, or replacements) in the new password *vs* the old.<br>
`enforce_for_root`: as per instructions!

(‡) **NOTE**: It is possible to use a *credit* system, wherein `ucredit`, `lcredit`, `dcredit` and `ocredit`—for *other*—are tallied against the `minlen` requirement. In this system, the value numbers are positive.
- You can list the Linux services that use Linux-PAM with `ls /etc/pam.d`
- For more details, open the **man** pages, `man 5 pam.d` and `man 8 pam_pwquality`.

Another interesting item one can modify in `/etc/pam.d/common-password` is the algorithm used to encrypt the passwords. User account information is kept in `/etc/passwd`—accessible through `getent passwd`—, but the nifty way to open/edit this file is with command **vipw**. Encrypted passwords are stored in `/etc/shadow`.
- Find more on these files in the **man** pages, `man 5 passwd` and `man 5 shadow`.

Type **reboot** to restart the machine if you wish to try the new password conditions. The command to change passwords is `passwd [LOGIN]`. If no `LOGIN` is typed, the current user is presumed.
- Notice that the `root` user does not have to present the current password before typing a new one, neither for itself nor other users. Therefore, the minimum 7-character difference with the old password rule is not applicable to `root`, in accordance with the project document!

#### A.3.e sudo installation & configuration

**sudo** (superuser do) will allow any user to adopt omnipotent `root` abilities. Therefore, it must be be properly configured. Start by installing the **sudo** package:
> apt -y install sudo
-  You may print the **sudo** version string (and any configured plugin) with `sudo -V | more`.

One could add to the main configuration file, `/etc/sudoers`, directly. But in it—try **visudo** in the command line interface—one reads that new content should be incorporated through the `/etc/sudoers.d` folder instead.

**sudoers** mostly contains *users specifications* following the syntax `User Host = (Runas) Command`. This reads as *User may run Command as the Runas user on Host*.

`User` and `Runas` may by usernames, groupnames prefixed with `%`, numeric UIDs prefixed with `#`, or numeric GIDs prefixed with `%#`.<br>
`Host` may be a hostname, IP address, or a whole network.<br>
`Command` is the full path to an executable.

Any or all of the above may be the special keyword `ALL`, valid for everyone, everywhere, and everything.
- The optional clause `Runas` controls the target user and group **sudo** will run the `Command` as. It determines which combinations of `-u` and `-g` will be valid with **sudo**. In its absence, the assumed identity will be *superuser*, *i.e.* `root`.
- It is possible to fine-grain the permissions to an incredible detail. For more information, check the **man** page at `man 5 sudoers` (paying special attention to the **Runas_Spec** section).

The project does not instruct us to tamper with the **sudo** specifications. If fact, the two active lines in **sudoers** remain

	# User privilege specification
	root	ALL=(ALL:ALL) ALL

	# Allow members of group sudo to execute any command
	%sudo	ALL=(ALL:ALL) ALL

But we are instructed to tweak its configuration with additional **sudo** parameters. Let's do that, calling the new config **Born2beroot** (§):
- Any filename not ending with tilde `~` or containing a dot `.` will do.
> vi /etc/sudoers.d/Born2beroot (§)(†)

[**TIP**: Copying these lines is burdensome and prone to errors. A better solution is to **ssh** yourself into the guest machine from the host—check how in **§ B.5.g SSH**—, **su** into `root`, and *copy-paste* the code from this guide or the `src/` folder in this Git repository into the newly created file.]

	Defaults	badpass_message="Prueba otra vez, bobo" (§)
	Defaults	log_input, log_output
	Defaults	iolog_dir="/var/log/sudo/"
	Defaults	logfile="/var/log/sudo/sudo.logs" (§)
	Defaults	requiretty
	Defaults	secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
	Defaults!/usr/bin/sudoreplay !log_output
	Defaults!/sbin/reboot !log_output
- Technically, we could list all the `Defaults` parameters of this file into a single line, separated with commas.
- For more details on the *Default_Entry* possibilities, search in the manual for the **SUDOERS OPTIONS** section.

`badpass_message`: unfortunately, strict compliance with the project document bars the very colorful `Defaults   insults`!<br>
`log_input, log_output`: every input and output action has to be archived.
- Output logs may be viewed with the **sudoreplay** utility, which can also be used to list or search the available logs. Check `man 8 sudoreplay`, and **§ B.5.e sudo** for a working example.

`iolog_dir`: top-level directory where the logs will be stored, as instructed by the document.<br>
`logfile`: human-readable log file.<br>
`requiretty`: will only allow **sudo** commands coming out of a real tty terminal, not something like, say, a **cron** script (which we shall shortly see).<br>
`secure_path`: **sudo** will use this value in place of the user's PATH environment variable.
- Note that the example path in the document includes a `/snap/bin`. However, we don't have any **snap** applications packaged in our machine.

`Defaults!… !log_output`: we will ***not*** be logging output from the **sudoreplay** nor **reboot** commands. Without the first of these provisions, the act of running **sudoreplay** on itself would result in a very peculiar recursion: the program recording itself running a recording!

Finally, `Defaults   passwd_tries=3` is unnecessary as, by default, **sudo** logs a failure and exits after three attempts.

Create the folder for the log files with `mkdir /var/log/sudo`.<br>
[**NOTE**: A first use of **sudo** from within `root` would also create this folder.]

#### A.3.f Adding new groups

You can find all the groups in the database stored in the `/etc/group` file, including their GID numbers and members. If you are interested in printing their names only, consider using the following piped commands:
> awk -F : '{print $1}' /etc/group | sort | more

To figure out the groups the current user is a member of, type `id -Gn`. Now switch from the `root` user you are (probably) logged as, to your typical login account—`su rtorrent` (§)—, and try again. You may return to `root` with a simple **exit** command. But before you do, attempt to use **sudo** from the ordinary account: `sudo echo "hello, world"`. You should get an error message ("XXX is not in the sudoers file.") because user XXX is not a member of the `sudo` group. Recall from the previous section (**§ A.3.e sudo installation & configuration**) that only `root` and members of group `sudo` have permission to run **sudo**.

Back as `root`, create the new `user42` group the document asks for and include the ordinary-login user to it:
> groupadd -U rtorrent user42 (§)

Now add the same user to the `sudo` group with one of the following commands,
> groupmod -aU rtorrent sudo (§)

or alternatively,
> usermod -aG sudo rtorrent (§)

Both edit the user's details and the group's membership.<br>
[**NOTE**:  The `-a` option (*append*) is crucial. Without it, the command will completely replace the user/group lists. This is not important with the **groupmod** command *in this case*—because we start with an empty group—, but it would be dramatic in the case of **usermod** to expel the user from all groups, including their own primary group, just to get them into `sudo`!]
- Open the **man** pages for further details: `man 8 groupadd`, `man 8 groupmod`, and `man 8 usermod`.

Double-check everything went right with `id rtorrent -Gn` (§). If you switch users again, **sudo** should now work with the login user.

There is an alternative solution to the commands used in this section: **addgroup** and **adduser**. These are actually *interactive* Perl scripts working with the original bin commands. You may locate them with `which addgroup` and `which adduser`, and find more information in the **man** page, common for both, `man 8 adduser`.

#### A.3.g Simple script

The next task is to write a Bash script, **monitoring.sh**. We choose to place this script in the `/usr/local/sbin` folder, which conveniently is included in the PATH environment variable of our Linux system. (You can check this fact with `printenv PATH`.) Thus placed, the script can be executed everywhere without specifying its full path.
- A non-administrator's PATH does not include the `/sbin` folders.

Using *everyone's* favorite text editor,
> vi /usr/local/sbin/monitoring.sh (†)

type the following Bash commands (or follow the TIP found in **§ A.3.e sudo installation & configuration**):

	#!/bin/bash

	Architecture of OS & kernel version
	arch=$(uname -srvmo)

	# Physical processors<br>
	pcpu=$(lscpu | awk -F : '
		/^Core\(s\) per socket/ {mult=$2}
		/^Socket\(s\)/ {mult*=$2}
		END {print mult}')

	# Virtual processors
	vcpu=$(nproc)

	# RAM available/total MB (%)
	rama=$(free -m | awk '/^Mem:/ {print $7}')
	ramt=$(free -m | awk '/^Mem:/ {print $2}')
	ramp=$(printf '%.2f' $((10000*rama/ramt))e-2)

	# Disk available/total GB (%)
	temp=$(df -x tmpfs -x devtmpfs --total | grep ^total)
	tmpa=$(echo $temp | awk '{print $4}')
	tmpt=$(echo $temp | awk '{print $2}')
	dska=$(printf '%.2f' $((100*tmpa/1024/1024))e-2)
	dskt=$(printf '%.2f' $((100*tmpt/1024/1024))e-2)
	dskp=$(printf '%.2f' $((10000*tmpa/tmpt))e-2)

	# CPU utilization rate (%)
	cpup=$((100-$(vmstat 1 2 | tail -1 | awk '{print $15}')))

	# Last reboot (yyyy-mm-dd HH:MM:SS)
	lrbt=$(uptime -s)

	# LVM in use
	lvmu=$(if grep -q '/dev/mapper/' /etc/fstab
		then echo yes
		else echo no
		fi)

	# Active TCP and UDP connections
	acon=$(ss -Htu -o state connected | wc -l)

	# Logged users
	logu=$(who | wc -l)

	# IPv4 and MAC addresses

	defd=$(ip route | grep '^default via' | grep -oP '\bdev\s\K\w+')
	ipv4=$(ip address show $defd | grep -Eo 'inet ([0-9]*\.){3}[0-9]*' | awk '{print $2}')
	maca=$(ip link show $defd | grep link | awk '{print $2}')

	# sudo usage
	sudo=$(journalctl _COMM=sudo | grep COMMAND | wc -l)

	wall "	Architecture: $arch
		Physical processor(s): $pcpu
		Virtual processor(s): $vcpu
		Available memory: $rama/$ramt MB ($ramp%)
		Available disk space: $dska/$dskt GB ($dskp%)
		CPU usage: $cpup%
		Last reboot: $lrbt
		LVM in use? $lvmu
		Active Internet (TCP and UDP) connections: $acon
		Logged users: $logu
		Network: IPv4 $ipv4 MAC $maca
		Executed sudo commands: $sudo"

Finally, change the permissions on the script so everybody can actually execute it:
> chmod +x /usr/local/sbin/monitoring.sh

`Architecture`: `uname -srvmo` prints the *kernel name* (`-s`), *kernel release* (`-r`), *kernel version* (`-v`), *machine hardware name* (`-m`), and *operating system* (`-o`).
- A simpler command `uname -a` (or `uname --all`) prints *all* system information, including the unsolicited network node hostname—`rtorrent42` (§)—.
- Manual: `man 1 uname`.

`Physical processor(s)`: **lscpu** displays information on the CPU architecture. The number of physical cores is the product of `Core(s) per socket` with `Socket(s)`. Line `CPU(s)` actually displays the number of *logical* cores, that is, the physical number just calculated multiplied by the *hyper-threads* in each core, `Thread(s) per core`.
- An alternative (and convoluted) route is to read the contents of the `/proc/cpuinfo` text file. A plethora of data is printed for the *logical* CPUs, grouped beneath each numbered processor:<br>
`processor`: identifies the logical processor.<br>
`physical id`: identifies the socket.<br>
`siblings`: number of threads on the socket.<br>
`core id`: identifies the core on a socket.<br>
`cpu cores`: number of cores on the socket.<br>
*Hyper-threading* is engaged when `siblings` differs to `cpu cores`. The number of `processor` entries divided by the *hyper-threads* (`siblings`/`cpu cores`) equals the physical cores present.
- Manual: `man 1 lscpu`.

`Virtual processor(s)`: `nproc --all` prints all installed processors.
- The **nproc** command is often used in shell scripts to check the number of available threads.
- Alternative solutions include `lscpu | awk -F : '/^CPU\(s\)/ {print $2}' | sed 's/ //g'` and `grep -c processor /proc/cpuinfo`.
- Manual: `man 1 nproc`.

`Available memory`: `free -m` (or `free --mebi`) uses data provided by file `/proc/meminfo`. Available memory (seventh column in **free**'s ouptut) is an estimation of how much memory is avaliable for starting new applications without relying on swapping. It considers memory lost to paging and other unclaimable bits. Memory total (second column) is below the theoretical installed (*i.e.*, 2,048 MB in our machine) because the kernel keeps some for itself. Another chunk is probably gobbled by the hardware.
- The default size in **free** and `/proc/meminfo` is 1 kB = 1,024 bytes, hence the option `-m` (1 MB = 1,024 kB).
- Bash operates with integers, not floating-point arithmetic. Notice the trick of multiplying by 100 and appending `e-2` in the `printf` command argument, for obtaining two decimal points.
- Manuals: `man 1 free`, `man 1 printf`.

`Available disk space`: `df -x tmpfs -x devtmpfs --total` (disk filesystem) checks disk usage on a mounted filesystem, in 1 kB blocks. Unfortunately, the command includes some *tmpfs* (temporary file system) and one *devtmpfs* for device files (the interfaces between actual physical devices and the user). Both are virtual filesystems created to store files in volatile (RAM) memory… Option `-x` (`--exclude-type`) omits those entries and option `--total` conveniently adds the columns for us. Giga-sized blocks (option `-BG`) are too coarse for an accurate measurement and some arithmetic calculations must follow.
- Manual: `man 1 df`.

`CPU usage`: `vmstat 1 2` (virtual memory statistics) reports CPU activity in near-real time. The first argument is the *delay* between updates in seconds, while the second prescribes *count* determinations. The first report produced gives averages since the last reboot, not what we are after, and so we turn our attention to the second (last) row. We are interested in column `id` (*idle*, 15th), the complement of the utilization rate.
- On the other hand, CPU *load* is defined as the number of processes using or waiting to use one core at a single point in time. It can be determined with command **uptime**.
- Manual: `man 8 vmstat`.

`Last reboot`: `uptime -s` (or `uptime --since`).
- Manual: `man 1 uptime`.

`LVM in use`? one needs to find a single mounted filesystem whose device name starts with `/dev/mapper/`. Available options are commands **df**, **mount**, and **blkid**. Alternatively, one can read the system configuration file `/etc/fstab`. Instead of by name, it is also possible to limit the search by device type, *lvm*. In this case, consider command **lsblk**.
- Manuals: `man 1 df`, `man 8 mount`, `man 8 blkid`, `man 8 lsblk`.

`Active Internet (TCP and UDP) connections`: `ss -Htu -o state connected`. Command **netsat** has been superseded by **ss** (socket statistics). Options `-tu` will display only sockets of the TCP and UDP protocols, filtered with `-o state connected` to allow all states except *listening* and *closed*. Option `-H` (`--no-header`) simplifies the tally by suppressing the header.
- Option `-a` (or `--all`) displays all *established* connections for TCP, but many unwelcomed results for UDP as well.
- Manual: `man 8 ss`.

`Logged users`: simple count of **who** results.
- Equally valid is the `users | wc -w` combination.
- Manuals: `man 1 who`, `man 1 users`.

`Network`: classic command **ifconfig** has also been deprecated, use **ip** instead. The first step is to identify the *default* device in the routing table, `ip route`. With this id, finding the required addresses is but a simple scan for certain keywords among the protocol address management, `ip address`, and the network device configuration, `ip link`.
- The `grep` command to determine the device id, which first searches for keyword `dev`, resorts to a Perl *regexp* because the more typical "lookbehind" syntax, `(?<=)`, is not interpreted with the regular nor the extended pattern syntaxes.
- The matching regular expression after the `ip address show` command is particular to the IPv4 protocol—32-bit valid range from `0.0.0.0` to `255.255.255.255`—. We can forgo the `-4` option in `ip -4 address show`, short for `-family inet`.
- Command `hostname -I` (or `hostname --all-ip-addresses`) is a bit unreliable. It will print *all* IP addresses in no particular order.
- Manuals: `man 8 ip`, `man 8 ip-address`, `man 8 ip-route`, `man 8 ip-link`, `man 1 hostname`.

`Executed sudo commands`: `journalctl _COMM=sudo`. You can monitor **sudo** activity through **journalctl**. This is a system logging program that comes with every Linux distribution that uses **systemd**, a software suite that provides all manner of services and utilities.
- Manuals: `man 1 journalctl`, `man 1 systemd`, `man 7 systemd.journal-fields` (for details regarding *trusted field* `_COMM`).

Broadcasting the information: **wall** (write to all).
- The project document leaves the inclusion of the banner as optional. It can be removed with `wall -n` (`--nobanner`).
- Manual: `man 1 wall`.

![Script broadcast](src/img02.png "Behold the script in all its glory!")

[**NOTE**: For this screenshot, the number or processors dedicated to the VM was increased to two. Three concurrent users had logged, two via **ssh**.]

#### A.3.h Timer scheduling

Another handy utility in the **systemd** service manager is the ability to establish timers. **systemd** operates through a system of *units*, wherein information on the processes to run is stored. With the task at hand, two such *units* are required: *Timer units* contain a special `[Timer]` section which defines when and how the timer activates. These specialized *units* end with filename extension `.timer`. *Service units* execute the processes provided in a `[Service]` section—**monitoring.sh** script for us—. Their filename extension is `.service`. Programming *units* is a field of it own, and the interested person may find `man 1 systemd`, `man 1 systemctl`, and `man 5 systemd.unit` useful.

It is recommended that the *unit* name that is activated and the *unit* name of the timer be named identically, except for the suffix. I've opted to call both *units* **monitoring** (§), for obvious reasons.

> systemctl edit --force --full monitoring.timer (§)

	[Unit]
	Description='monitoring' broadcast service timer

	[Timer]
	OnBootSec=10min
	OnUnitActiveSec=10min
	AccuracySec=1msec

	[Install]
	WantedBy=timers.target
- [Unit] section option:<br>
`Description`: A human readable name for the *unit*. This is used by **systemd** (and other UIs) as the label for the *unit*, so this string should identify rather than describe it.
- [Timer] section options:<br>
`OnBootSec`: defines a timer relative to when the machine was booted up.<br>
`OnUnitActiveSec`: defines a timer relative to when the *unit* the timer is activating was last activated.<br>
`AccuracySec`: specifies the accuracy the timer shall elapse with, that is, a time window starting with the time specified in `OnBootSec=` and `OnUnitActiveSec=` and ending the time configured with `AccuracySec=` later. Defaults to `1min`.<br>
`Unit` \<not included\>: the unit to activate when this timer elapses. This value defaults to a service that has the same name as the *timer unit* (but with the `.service` suffix).
- [Install] section option:<br>
`timer.target`: A special *target unit* that sets up all *timer units* and activates after boot. See `man 5 systemd.target` for details on *target units*, `man 7 systemd.special` for information on this particular target, and `man 7 bootup` for a rather fetching chart displaying the order in which *units* are pulled during the system boot-up.
- Timer-specific manuals: `man 5 systemd.timer` and `man 7 systemd.time`.

Option `--force` to open a new *unit* file for editing if non-existent—just our case—. Option `--full` to work on the original file, not a *drop-in*. *Drop-in* files are useful to alter an existing file without losing the original data. A *drop-in* will be used during the evaluation to override this 10-minute broadcast, see **§ B.5.h Script monitoring**.

> systemctl edit --force --full monitoring.service (§)

	[Unit]
	Description=Run the 'monitoring' broadcast script

	[Service]
	ExecStart=monitoring.sh
- [Service} section option:<br>
`ExecStart`: commands that are executed when this service is started.
- Service-specific manual: `man 5 systemd.service`.

**systemctl** will inform **systemd** about the new *units*. All that is left for us is to start the timer (option `--now`), and keep it around after a reboot (command `enable`):
> systemctl enable --now  monitoring.timer (§)
- Check on the timer with `systemctl status monitoring.timer` (§).
- As with any other **systemd** *unit*, you may check the journal: `journalctl --follow --unit monitoring.service` (§).
- Run `systemctl list-timers` to output a list of the active *timer units* in the system.
- By default, **systemd** services are configured to run as `root` user. That being the case, authorship of the broadcast will be superuser's and all other users logged to the server will not be able to block the (rather annoying) message popping every ten minutes using `mesg n`. More information on this command may be found at `man 1 mesg`.
- Should you prefer, you may incorporate the new *units* into **systemd** with a regular text editor and then reload the ***whole*** configuration (rerun all *generators*—executables of dynamic *units*—, reload all *unit* files, and recreate the entire dependency tree):<br>
> vi /etc/systemd/system/monitoring.timer (§)(†)<br>
> vi /etc/systemd/system/monitoring.service (§)(†)<br>
> systemctl daemon-reload

This timer works like "dominoes falling". Only the first broadcat, `OnBootSec`, is controlled by an external event. Every broadcast thereafter depends on its previous activation, `OnUnitActiveSec`. Therefore, if more than ten minutes have elapsed since system boot, nothing will happen unless you **reboot**.

##### A.3.h.1 Cron scheduling [ *Not recommended!* ]

The project document clearly states that "At server startup, the script will display [...] every 10 minutes". However, one would not err by much if he or she might programa a periodic timer to execute at *fixed* minutes of the clock, in intervals of ten minutes. If one accepts this *sleight of hand*, **cron** offers an easier alternative to **systemd**'s timer service.

**cron** is a *daemon*—a program that runs in the background but remains inactive until invoked—that executes scheduled commands. **cron** loads special *crontab* files into memory. Every minute henceforth, **cron** wakes and will execute those files marked to run at that specific moment. User *crontab* files (named after accounts in `/etc/passwd`) are located in a "user spool area" (`/var/spool/cron/crontabs/`). There also exists a "system-wide spool" comprising file `/etc/crontab` and the contents of the `/etc/cron.d/` folder. There are some differences in the methods of user *vs* system-wide *crontab* files.
- Unfortunately, the daemon sets up a different PATH variable, `/usr/bin:/bin`, leaving our monitoring script out.
- Much more information is to be found at `man 1 crontab` and `man 8 cron`.

1.- A first solution is to set `roots`'s *crontab* file in the "user spool". Command **crontab** set to edit (`-e`) will launch the editor specified by the VISUAL or EDITOR environment variables. After exiting from the editor, the modified *crontab* will be installed automatically.
> crontab -e
- Operate as user `root` if you are not logged as such, `sudo crontab -e`. (If, for any reason, you would want to change a third person's *crontab*, `sudo crontab -u other_user -e` (§).)

and type at the bottom of the file that pops up

	*/10 * * * *	/usr/local/sbin/monitoring.sh

The first five fields stand for *minute*, *hour*, *day of month*, *month*, and *day of week*. Whenever the clock agrees with these, the trailing command will be executed. An asterisk stands for the range *first-last*, *i.e.*, all. The first field includes `/10`, meaning *skip 10* over the range.
- One can check the contents of *crontab* files in the "user spool area" with option `-l`: `crontab -l` for the current login, `crontab -u rtorrent -l` (§) for our hero.
- *Crontab* syntax is best described in `man 5 crontab`.

2.- A second **cron** solution involves manually editing the system-wide *crontab*:
> vi /etc/crontab (†)

and attaching a new instruction at the bottom of the file, after the example tests,

	*/10 * * * *	root	monitoring.sh

Notice that this solution includes a sixth field with the intended user's login. Interestingly, the eighth line of the file is a PATH redefinition that includes our script's location, much simplifying the command.

Additionally, **cron** checks each minute to see if its spool directory's modification time (or the modification time on `/etc/crontab`) has changed, and if it has, **cron** will then examine the modification time on all *crontabs* and reload those which have changed. Thus, **cron** need not be restarted whenever a *crontab* file is modified.

---

### A.4 Setting a WordPress website

... WORK IN PROGRESS!

---

### A.5 Furnishing the website with services

Our virtual machine would be quite useless without a purpose. So let's make it four times worthy with as many installed services!

#### A.5.a Lightppd

#### A.5.b MariaDB

#### A.5.c PHP

#### A.5.d MongoDB (§)

[**NOTE**: Replace the content of this section with a fourth service of ***your*** choice!]

---

### A.6 The final signature

Power off the machine, ***never again*** to restart it.

The final stage of **Born2beroot** is to compute a checksum out of the machine's *VirtualBox Disk Image*, and *push* this result into the project repository for evaluation. We are instructed to use the SHA-1 algorithm and to leave the signature in a text file named **signature.txt**. (In a real world case, we would not employ SHA-1, cryptographically deprecated more than a decade ago, and the checksum file itself should also be signed for proof against tampering with some sort of public key.)

Navigate to the folder where the VM is lodged, `/System/Volumes/Data/sgoinfre/Perso/rtorrent/` (§), and locate the image. It will be a chunky file ending with the `.vdi` extension, in my case **Born2beroot_Debian12.1.0.vdi** (§).
> shasum Born2beroot_Debian12.1.0.vdi > signature.txt (§)

The output's format will resemble

	40f7a1b8a8bfecdc9e7c1454f0cde50005b183f1  Born2beroot_Debian12.1.0.vdi (§)
- Inside the VM, the preferred Debian command would have been **sha1sum**. **shasum** is actually a Perl script, which falls back to SHA-1 as its default algorithm.
- Check manuals `man 1 shasum` and `man 1 sha1sum` (the latter only from within Debian).

Verifying the integrity of the virtual machine—***do not*** power the machine as *any* change in its content, however slim, will alter any subsequent checksums from the evaluators—is as easy as running
> shasum -c signature.txt

Move **signature.txt** to the empty folder where **git** cloned the *intra*'s project, and finish this ordeal.

**CONGRATULATIONS!**

---

## B. Preparing for the project defense

![Scale for project **Born2beroot**](src/img08.png "Copy the URL to the Git repository")

**NOTE**: Answers to questions from the evaluator, marked with `[A]` in this guide, may be very opinionated or completely unrelated to the reader's experience. Use common sense and supply your own answers where personal observations are expected.

### B.1 Introduction

![Introduction](src/img09.png)

---

### B.2 Guidelines

![Guidelines](src/img10.png)

---

### B.3 Attachments

[![Attachments](src/img11.png "Click to open 'en.subject.pdf', in this repository")](https://github.com/R-Torrent/42Barcelona-Projects/blob/master/42-cursus/common-core-rank01/Born2beroot/en.subject.pdf)

---

### B.4 Preliminaries

![Preliminaries](src/img12.png)

#### B.4.a Preliminary tests

![Preliminary tests](src/img13.png)

---

### B.5 General instructions

![General instructions](src/img14.png)

#### B.5.a General instructions

![General instructions](src/img15.png)

Navigate to the student's folder where the `.vdi` image resides (check **§ A.1.a Name and Operating System**), somewhere in the `SGoinfre` folder, and type
> shasum -c [*path-to-cloned-git-project/*]signature.txt

The answer should be a resounding `Born2beroot_Debian12.1.0.vdi: OK` (§).

Comparing the SHA checksums with the **diff** command is also acceptable. Check that the **signature.txt** text file and the `shasum Born2beroot_Debian12.1.0.vdi` output are equally formatted before pronouncing a no-good result.

**IMPORTANT: Clone the disk image with VirtualBox before proceeding *any* further.**

---

### B.6 Mandatory part

![Mandatory part](src/img16.png)

#### B.6.a Project overview

![Project overview](src/img17.png)

[Q] Explain simply how a virtual machine works.

[A] A virtual machine packages an operating system and application with a description of the compute resources needed to run it, such as the CPU, memory, storage, and networking. When this virtual machine is deployed to a host computer, software called a *hypervisor* reads the description and provides the requested hardware resources. "Type 1" *hypervisors* run directly on the hardware of the host machine, and are best suited to server, desktop and application virtualization. "Type 2" *hypervisors*, such as **Oracle**'s **VirtualBox**, run on top of the host's OS, which actually manages calls to the hardware resources. They are more of a developing and testing tool.

[Q] Explain simply the choice of operating system.

[A] Between **Debian** and **Rocky Linux**, my choice was immediate. At home, my **Raspberry Pi** single-board computer runs on **Raspbian** OS, a fork from the **Debian Linux** distribution. It was a case of going with what is familiar.

[Q] Explain simply the differences between **Rocky** and **Debian**.

[A] **Rocky Linux** is a distribution 100% compatible with **Red Hat Enterprise Linux**, a different Linux family altogether from **Debian Linux**. These families manifestly differ in the package manager/dependency resolver combo: **RPM** for **Rocky** with **yum** as its front-end *vs* **dpkg** for **Debian** with **APT** as its user interface. But it's in their philosophies where these distros completely diverge: **Rocky** strives to mantain compatibility with a commercial Linux distribution while keeping *open source*, whereas **Debian** embraces *free software*. The latter has quicker development time, easier (for the end-user) and regular updating, and a more numerous following that translates into faster bug-fixing.

[Q] Explain simply the purpose of virtual machines.

[A] Three purposes come to mind: First, a VM provides an environment that is isolated from the rest of a system, so whatever is running inside a VM won’t interfere with anything else running on the host hardware. Because VMs are isolated, they are a good option for testing new applications or setting up a production environment. Second, you can also run a single purpose VM to support a specific process, *independent* of the actual host platform. And third, most operating system and application deployments only use a small amount of the physical resources available to them if deployed "bare metal". By virtualizing the servers, many can be placed onto each physical server to improve hardware utilization.

[Q] Explain simply the difference between **aptitude** and **apt**, and what **APPArmor** is.

[A] **APT** is a vast undertaking developed by the Debian Project to simplify the process of managing software through the  automation of the retrieval, configuration, and installation of software pacakges. Its first front-end was command-line based **apt-get** (`man 8 apt-get`), followed by **apt** (`man 8 apt`), which also includes **apt-cache**'s functionalities (`man 8 apt-cache`). **aptitude** is an external project that functions over the same libraries with few minor differences and yet, it provides a terminal menu interface.

**APPArmor** is a security extension for the Linux kernel that confines programs to a limited set of resources.

Launch the clone VM, use the passphrase to decrypt the LVM partitions—`Born2beroot` (§)—, and follow with a non-administrator account to login into the machine, `rtorrent` (§). The password should respect the restrictions imposed by the document.

We can find out if **APPArmor** is enabled with
> aa-enabled

and get a reassuring `Yes` back. A tortuous alternative is `cat /sys/module/apparmor/parameters/enabled` (contains `Y` if true).

To list all loaded **APPArmor** profiles for applications and processes and detail their status (*enforced*, *complain*, *unconfined*):
> sudo aa-status

**APPArmor** profiles live in `/etc/apparmor.d/`.

#### B.6.b Simple setup

![Simple setup](src/img18.png)

The lack of a graphic envirornment should be obvious, but it can be verified with
> echo $DESKTOP_SESSION

or
> ls /usr/bin/*session

where one should only find `/usr/bin/dbus-run-session`, or even
> type Xorg

where `Xorg` should not be found.

Verify that UFW service is up and running with
> sudo service ufw status

Same for the SSH service
> sudo service ssh status

The OS can be determined with
> uname -o

which will print `GNU/Linux`, with the only mention to the "Debian" distribution to be found in the kernel version:
> uname -v

The recommended approach is
> head -n 2 /etc/os-release

with a nicer looking `PRETTY_NAME="Debian GNU/Linux 12 (bookworm)"` (or the current Debian release) and `NAME="Debian GNU/Linux"`.

#### B.6.c User

![User](src/img19.png)

We can confirm the presence of our login with
> cat /etc/passwd | sed -n /^rtorrent/p (§)

but the following is more straightforward
> getent passwd rtorrent (§)

Next, we list the members of `sudo` and `user42` groups
> cat /etc/group | sed -n /^sudo/p<br>
> cat /etc/group | sed -n /^user42/p

but, again, better with the `getent` command
> getent group sudo<br>
> getent group user42

or best, just list the groups the user is a member of with
> id -Gn

Now for the new user, say `new_user` (§), just as we did in **§ A.3.f Adding new groups**, we are going to favor the native bin command (**useradd**, see `man 8 useradd`) over the "user friendly" Perl script (**adduser**, see `man 8 adduser`) that runs on said command:
> sudo useradd -m -s /bin/bash new_user (§)<br>
> sudo passwd new_user (§)

Option `-m` will create a home directory for this user, and option `-s /bin/bash` will override the default login shell so that it matches `root` and `rtorrent`'s (§).
[**NOTE**: This is the moment to prove that new passwords adhere to the policy; try-out various forbidden patterns.]

Default characteristics for this new user can be examined with `sudo useradd -D`, which actually displays information stored in `/etc/default/useradd`. Most of the values in the file are deactivated! As anticipated in **§ A.3.d Strong password policy**, the configuration variables in `/etc/login.defs` also change the behaviour of this tool. For example, **useradd** plus `USERGROUPS_ENAB yes` will create by default a group with the name of the user. This is readily established with
> getent passwd new_user (§)

and
> id new_user (§)

It is very easy to verify the passwords' aging rules with
> sudo chage -l new_user (§)

We are asked to create an `evaluating` group and to assign the new user to it. We can do both with
> sudo groupadd -U new_user evaluating (§)

As per instructions, we can check that the user belongs to this group:
> getent group evaluating

[Q] Explain the advantages of the password policy, as well as the advantages and disadvantages of its implementation.

[A] Really *any* password policy that forces out some effort from the users is desirable. Left to their own devices, people will produce such lazy watchwords as "123456", "qwerty", "password", or "baby"!

The advantage of this project's implementation is that its merits as a secure scheme—the encrypted passwords and the PAM module—have been ascertained by countless users for decades. Personally however, as a disadvantage, I can't find the rule "Your password has to expire every 30 days." very practical. I can imagine *many* users forgoing any whiff of security by writing their monthly *secret* passwords on Post-its and sticking them to their screens.

#### B.6.d Hostname and partitions

![Hostname and partitions](src/img20.png)

The hostname of the VM should be obvious to all as it is included in the CLI prompt of the terminal: `[user-login]42`, in my case `rtorrent42` (§). Just to drive the point further, use command
> hostname

The document asks us to rename it, and so
> sudo vi /etc/hostname (†)
- Although not included in the instructions, changing the IP address mapping to the new hostname is not a bad idea: `sudo vi /etc/hosts` (†).

where we substitute all mentions of `rtorrent42` for `new_user42` (§). Next, one should reload the network configuration. However, the *lazy* approach is much preferable:
> sudo reboot

Behold the new hostname! Login with the the usual account, `rtorrent` (§), as `new_user` (§) still can't execute the **sudo** command.

To restore the name back, we shall employ the wow method, that is, **systemd**'s utility **hostnamectl**:
> sudo hostnamectl hostname rtorrent42 (§)
- For reference, `man 1 hostnamectl`.

A simple `exit` will push the change through this time.

We can exhibit the machine's partitions with command **lsblk** (list block devices):

![**lsblk** output](src/img03.png "Notice all the bonus partitions")

[Q] Explain simply how **LVM** works and what it is all about.

[A] **LVM** stands for Logical Volume Manager, a tool that allows you to create, resize, delete, and extend partitions on Linux servers. It breaks physical volumes—hard disks, their partitions, external storage devices…—into physical chunks (*physical extents*, PEs) which are mapped one-to-one into *logical extents*, LEs. These are pooled together to form *logical groups*, whence LEs are concatenated, split, and merged at will into *logical volumes* acting as virtual disk partitions.

#### B.6.e sudo

![sudo](src/img21.png)

With `sudo -V` we can read the version of the installed **sudo** (and the versions of the security policy and I/O plugins). We can unequivocally verify if the package is installed with `dpkg -s sudo`.

Adding the new user into `sudo` group is relatively easy:
> sudo groupmod -aU new_user sudo (§)

or
> sudo usermod -aG sudo new_user (§)

Finally, exit from `rtorrent` (§) for the last time and login with the `new_user` (§).

**sudo** is a very special command that allows selected users to run designated commands, on designated machines, while impersonating other designated users. It is a very critical operation that necessitates the fine adjustment of a special file, `/etc/sudoers/` and the rest of the configuration files added into the `/etc/sudoers.d` folder. It is used mostly to appropriate `root`'s privileges, but any user or group can be feigned.

As a simple demonstration,
> whomai<br>
> sudo whoami<br>
> sudo -u rtorrent whoami

The **sudoers** file actually enables all members of the `sudo` group to "execute any command", as can be read off its specifications, near the bottom:
> sudo visudo

The project document mandated a set of additional restrictions on **sudo** that are kept in the **sudoers.d** folder:
> cat /etc/sudoers.d/Born2beroot (§)

Notice one actually needs admin status, *i.e.* `root`, to edit both config files!

The project `.pdf` also expects that **sudo** activity be monitored and logged into the `/var/log/sudo/` folder. These records are kept in a "human-readable" file, **sudo.logs** (§),
> sudo ls /var/log/sudo<br>
> sudo cat /var/log/sudo/sudo.logs (§)

and not so friendly streams accesible with the **sudoreplay** command:
> sudo sudoreplay -d /var/log/sudo -l

From this list we can scan through all **sudo** operations, optionally restricted to those commands that match a predicate [see below]. We are interested on the `TSID` sequences of the concrete **sudo** sessions. For a pleasing example, run
> sudo apt update

(This command will download the latest package information.) Next, enable the "list mode" in **sudoreplay**, with an extravagant predicate (which will hopefully pique readers into checking `man 8 sudoreplay`):
> sudo sudoreplay -d /var/log/sudo -l user new_user fromdate 'last hour'

![**sudoreplay** output](src/img07.png "Check the TSID for the 'apt update' command")

First of all, point out that the list of recorded **sudo** commands has indeed logged its two latest activities, as requested in the project document. Next, read the `TSID` from the `apt update` entry, in this case `00000I` (§), and replay the activity just as it was printed in the terminal!
> sudo sudeoreplay -d /var/log/sudo 00000I (§)
- You can pause the action by pressing the space bar; any key to resume.
- Convince the evaluator that you are watching a real-time recording, ***not reenacting*** `apt update`, by printing the contents of that particular "movie" with `sudo ls /var/log/sudo/00/00/0I/` (§) and `sudo cat /var/log/sudo/00/00/0I/ttyout` (§).
- A more persuasive case can be made with the command `sudo date`. Its replay will output the same ***stored*** date and time. Use `sudo sudoreplay -d /var/log/sudo -l command date` to figure the `TSID`.
- And an ***even more*** jaw-dropping demonstration can be made by typing into a text file, `sudo vi test.txt` (§)(†) and replaying that motion picture. Recall that the instructions request us to archive both the outputs ***and*** the inputs. The latter are stored in the session's `ttyin` folder. We can replay all the keystrokes, including our fumbling with **vi**'s interface, with `sudo sudoreplay -d /var/log/sudo -f ttyin 0000XX` (§). [Evidently, supply the pertinent `TSID`.]

#### B.6.f UFW

![UFW](src/img22.png)

We have already checked that the service is running, in **§ B.5.b Simple setup**, but we can also prove that it has been correctly installed:
> dpkg -s ufw

To show **UFW**'s version number, `sudo ufw version`.

[Q] Explain simply what **UFW** is and the value of using it.

[A] Uncomplicated Firewall (**UFW**) is an easy-to-use firewall utility that works on the Linux **iptables** (`man 8 iptables`) for configuration. A firewall is a network security system that monitors and controls incoming and outcoming network traffic based on predetermined security rules. Specifically, it is an administration tool for IPv4/IPv6 packet filtering and network address translation (**NAT**, a mapping table between public and private/internal IP addresses). **UFW**'s value is its intuitive simplicity.

To list its active rules—with a bit more information than heretofore seen—,
> sudo ufw status verbose

`Status: active                                               `<br>
`Logging: on (low)                                            `<br>
`Default: deny (incoming), allow (outgoing), disabled (routed)`<br>
`New profiles: skip                                           `<br>
`                                                             `<br>
`To                         Action      From                  `<br>
`--                         ------      ----                  `<br>
`4242                       ALLOW IN    Anywhere              `<br>
`4242 (v6)                  ALLOW IN    Anywhere (v6)         `

Clearly, only port `4242` accepts traffic, both for IPv4 and IPv6.

We are requested by the document to open another port, `8080`:
> sudo ufw allow 8080

We can confirm that port `8080` is indeed open with another `ufw status`, this time "numbering" the rules:
> sudo ufw status numbered

`Status: active                                               `<br>
`                                                             `<br>
`      To                         Action      From              `<br>
`      --                         ------      ----              `<br>
`[ 1] 4242                       ALLOW IN    Anywhere         `<br>
`[ 2] 8080                       ALLOW IN    Anywhere         `<br>
`[ 3] 4242 (v6)                  ALLOW IN    Anywhere (v6)    `<br>
`[ 4] 8080 (v6)                  ALLOW IN    Anywhere (v6)    `

There are two ways to remove the additional new rules:

1.- By rule number. This justifies the need of the previous `numbered` display,
> sudo ufw delete 2<br>
> sudo ufw delete 3

Both operations must be confirmed (`Proceed with operation (y|n)?`).

2.- By rule specification. This reverts a previous command,
> sudo ufw delete allow 8080

End with a `sudo ufw status` to attest that everything is back to the starting conditions.

#### B.6.g SSH

![SSH](src/img23.png)

As before, we know the service is up and running from **§ B.5.b Simple setup**, but we can also prove that the package has been correctly installed:
> dpkg -s openssh-server

To display **SSH**'s version number, `ssh -V`.

[Q] Explain basically what **SSH** is and the value of using it.

[A] Secure Shell (**SSH**) is a protocol for secure remote access and file transfer over an unsafe network. It uses public-key cryptography to authenticate clients and servers, and encrypt the connection. Its value is obvious: to prevent a malicious third party from eavesdropping.

The **SSH** daemon is listening to port `4242`, something easily proven by reading the output from the `service ssh status` (refer to the screen capture in **§ A.3.b Secure Shell setup**). A more direct method is to output the configuration file
> sudo sshd -T | head -1
- Option `-T` really tests the validity of the configuration file, but it prints its contents too.
- **sshd** forks a new daemon for each incoming connection. It is normally started at boot from `/etc/init.d/ssh`, and can override the options set forth in the `/etc/ssh/sshd_config` file (again, read **§ A.3.b Secure Shell setup**).
- Check `man 8 sshd` for more.

We can connect into our Debian machine from the *host* machine's terminal with a simple **ssh** command after supplying the *host port* we selected in **§ A.3.a Setting the ports**—`1717` (§) in this guide—
> ssh new_user@localhost -p 1717 (§)
- **VirtualBox** is responsible for rerouting the connection to port `4242` in the *guest* machine.

If, on the other hand, one chose ***not*** to reroute the `localhost` port, it is still possible to remotely access the VM using the ip address that has been broadcasted every 10 minutes since boot, `10.0.2.15` (§), with the correct port, `4242`.
> ssh new_user@10.0.2.15 -p 4242 (§)
- Do attempt to login as `root` via **ssh**. As instructed in the document, this effort ***should fail***.
- More information of the **ssh** command at `man 1 ssh`.

#### B.6.h Script monitoring

![Script monitoring](src/img24.png)

[Q] Explain simply how the script works by showing the code.

[A] Refer to **§ A.3.g Simple script** for details.

[Q] Explain simply what **cron** is.

[A] **cron** is a tool in the Linux system that runs scheduled jobs. It reads special files, *crontabs*, with the pertinent syntax to execute commands at the appointed minutes of the clock. Refer to **§ A.3.h.1 Cron scheduling** for details.

[Q] Explain simply how the student being evaluated set up their script so that it runs every 10 minutes from when the server starts.

**NOTE**: If **cron** was used to program the 10-minute broadcasts, look into **§ A.3.h.1 Cron scheduling** (if necessary) and skip to **§ B.5.h.1 Cron rescheduling**. If it was done through a **systemd** timer, keep reading.

[A] Refer to **§ A.3.h Timer scheduling** for details.

Locate our timer and service *units* among the myriad other *units* of the **systemd** jungle:
> systemctl list-timers<br>
> systemctl list-units --all monitoring.* (§)

and print their contents to explain its workings:
> systemctl cat monitoring.timer (§)<br>
> systemctl cat monitoring.service (§)
- Notice that the `cat` command prints the full path of the files, should we ever need them.

Furthermore, display their standings with
> systemctl status --quiet monitoring.timer (§)<br>
> systemctl status --quiet monitoring.service (§)
- The `--quiet` (or `-q`) option is to silence the remark that some information was not displayed for lack of permissions. A redo with **sudo** would establish that nothing new was gained after the hassle of typing the password.

Observe the cross-referencing `Triggers:` and `TriggeredBy:` lines in the `status` displays.

Our next task is to edit the timer so that it calls on the service every minute, cutting on the ten minute delays. We will ***not*** modify our existing *units*, but take full advantage of the *drop-in* mechanism of **systemd** to patch the timer. (Sadly, Debian's **systemctl** does not allow personalized names for the *drop-ins*.) The really neat bit is that one needs to include ***only*** the altered portions of the instructions:
> systemctl edit monitoring.timer (§)

	[Timer]
	OnBootSec=1min
	OnUnitActiveSec=1min

Assure the evaluator that only these changes are necessary with another `systemctl cat monitoring.timer` (§). The *drop-in* modifications are automatically incorporated into the full *unit* file. Note too that the original file is helpfully shown, commented, for easy reference during the editing. The broadcasts should start rolling every minute from here on!
- The *drop-in* will be named **override.conf** and placed in one `monitoring.timer.d/` (§) folder, located next to its parent file.
- The broadcasts will become excruciatingly bothersome very fast. You will have to `control + C` (`^C`) everytime and, every so often, the shell will actually recover to a readable state.

Display the updated status of the timer, `systemctl --quiet status monitoring.timer` (§). Find the **override.conf** *drop-in* in the read-out.

![**monitoring.timer status** output](src/img06.png "Notice the drop-in to the timer unit")

Now disable the timer, without actually deleting it, and wait a minute for its absence to go noticed before rebooting:
> sudo systemctl disable --now monitoring.timer (§)
- Option `--now` to stop immediately the *unit*, as well as suspending it on the next boot.
> sudo reboot

After login—keep to any non-administrator account— a `systemctl is-enabled monitoring.timer` (§) should show that the timer remains `disabled`.
- The same command on **monitoring.service** will return `static`, meaning "the **unit** file is not enabled, and has no provisions for enabling in the [Install] unit file section."
- The document also asks us to show that the script—or perhaps the *unit*, the wording is a bit unclear—remains unchanged. `ls -l /usr/local/sbin/monitoring.sh` (§) and `ls -l /etc/systemd/system/monitoring.timer` (§) will manifest that neither the permissions nor the modification dates on the files have been tampered.

We shall not re-enable the timer. Instead, we will demonstrate perhaps one of the virtues of **systemd**'s *drop-in* feature. Because our original 10-minute timer remains in the system, one needs only to discard the **override.conf** addition to undo the modifications:
> sudo systemctl revert monitoring.timer (§)
- The `monitoring.timer.d/` directory will be gone.
- The `revert` command will verbalize any changes, but a final `systemctl --quiet status monitoring.timer` (§) will display a `disabled` and yet original timer.

##### B.6.h.1 Cron rescheduling [ Not recommended! ]

The next step will depend on which *crontab* is responsible for running the script (see **§ A.3.h.1 Cron scheduling**). If that *crontab* is `root`'s, then
> sudo crontab -e

and edit the instruction at the bottom of the file so that it executes every minute of the clock:

	* * * * *	/usr/local/sbin/monitoring.sh

But if the system-wide *crontab* is in command, then
> sudo vi /etc/crontab (†)

and remove too the `/10` from the final instruction, after all the example tests:

	* * * * *	root	monitoring.sh

No need to restart **cron**. The change should take hold the minute after.

Once satisfied with the change, one is instructed to suspend the broadcast after start up. Now, the obvious solution would be to reopen the *crontab* file, again, and comment-out the instruction by prefixing a `#`. But the evaluation instructions are somewhat unclear on this point, and some might argue that they specifically forbid this, leaving us with the sole recourse of suspending the **cron** service itself:
> sudo systemctl disable cron
- Or do it the hard way, `sudo /etc/init.d/cron disable`

After restarting the machine, `sudo reboot`, it should be obvious that the script is not running. Furthermore, one must show that the script is located in the `/usr/local/sbin/` folder, unchanged, and that the *crontab* is intact too: `sudo crontab -l` or `cat /etc/crontab`, depending on which was used to execute.

---

### B.7 Bonus

![Bonus](src/img25.png)

#### B.7.a Bonus

![Bonus](src/img26.png)
