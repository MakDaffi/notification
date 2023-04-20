%define _unpackaged_files_terminate_build 1

Name: notify
Version: 0.1
Release: alt1

Summary: Display system time every hour
License: GPLv3+
Group: Other

BuildRequires: make
BuildRequires: gcc-c++
BuildRequires: libsystemd-devel

Source0: %name-%version.tar

%description
This test program displays system date and time every hour via notification

%prep
%setup -q

%build
%make_build

%install
mkdir -p \
	%buildroot/bin
install -Dm0755 %name %buildroot/bin/

mkdir -p \
	%buildroot%_sysconfdir/xdg/systemd/user/
cp %name.timer %name.service \
	%buildroot%_sysconfdir/xdg/systemd/user/

%files
/bin/%name
/etc/xdg/systemd/user/%name.service
/etc/xdg/systemd/user/%name.timer

%changelog
* Thu Apr 13 2023 Sergey Okunkov <sok@altlinux.org> 0.1-alt1
- Finished my task

