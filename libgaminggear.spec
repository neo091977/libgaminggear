%define vmajor 0
%define vminor 4
%define vmicro 0

Name: libgaminggear
Version: %{vmajor}.%{vminor}.%{vmicro}
Release: 1
License: GPL
Source: %{name}-%{version}.tar.bz2
BuildRoot: %{_tmppath}/%{name}-%{version}-build
BuildRequires: cmake >= 2.6.4
BuildRequires: gtk2-devel >= 2.20
BuildRequires: sqlite >= 3.7
BuildRequires: libcanberra-devel
BuildRequires: libnotify-devel
ExclusiveOS: linux
Prefix: /usr
URL: http://sourceforge.net/projects/libgaminggear/
Packager: Stefan Achatz <erazor_de@users.sourceforge.net>

Summary: Libraries for gaming input devices
Group: System Environment/Libraries

%package devel
Requires: libgaminggear
Summary: Development headers for libgaminggear.
Group: Development/Libraries

%description
Libgaminggear provides functions and widgets common for gaming input devices.

%description devel
Libgaminggear provides functions and widgets common for gaming input devices.
Here are the development headers needed to compile software that uses libgaminggear.

%prep
%setup -q -n %{name}-%{version}
%{__mkdir} build
cd build
cmake -DCMAKE_INSTALL_PREFIX="%{prefix}" ..

%build
cd build
%{__make} -r %{?_smp_mflags}

%install
cd build
%{__rm} -rf "%{buildroot}"
%{__make} -r %{?_smp_mflags} DESTDIR="%{buildroot}" install

%clean
%{__rm} -rf "%{buildroot}"

%post
/sbin/ldconfig
touch --no-create %{prefix}/share/icons/hicolor &>/dev/null || :

%postun
/sbin/ldconfig
if [ $1 -eq 0 ] ; then
  touch --no-create %{prefix}/share/icons/hicolor &>/dev/null
  gtk-update-icon-cache %{prefix}/share/icons/hicolor &>dev/null || :
fi

%posttrans
gtk-update-icon-cache %{prefix}/share/icons/hicolor &>dev/null || :

%files
%defattr(-,root,root)
%doc INSTALL README COPYING Changelog
%{prefix}/lib*/gaminggear-%{vmajor}
%{prefix}/share/gaminggear/icons
/etc/ld.so.conf.d/gaminggear-%{vmajor}.conf

%files devel
%defattr(-,root,root)
%{prefix}/include/gaminggear-%{vmajor}/gaminggear
%{prefix}/share/gaminggear/html
/usr/share/pkgconfig/gaminggear-%{vmajor}.pc
/usr/share/cmake/Modules/FindGAMINGGEAR%{vmajor}.cmake

%changelog
* Fri Jul 04 2014 Stefan Achatz <erazor_de@users.sourceforge.net> 0.4.0-1
- Initial version
