%define vmajor 0
%define vminor 6
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
BuildRequires: doxygen
ExclusiveOS: linux
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
cmake -DCMAKE_INSTALL_PREFIX="%{_prefix}" -DCMAKE_BUILD_TYPE=Release -DINSTALL_LIBDIR="%{_libdir}" -DWITH_DOC=TRUE ..

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
%{_libdir}/libgaminggear*
%{_datadir}/gaminggear/icons

%files devel
%defattr(-,root,root)
%{_includedir}/gaminggear-%{vmajor}
%{_datadir}/gaminggear/html
%{_datadir}/pkgconfig/gaminggear-%{vmajor}.pc
%{_datadir}/cmake/Modules/FindGAMINGGEAR%{vmajor}.cmake

%changelog
* Mon Feb 02 2015 Stefan Achatz <erazor_de@users.sourceforge.net> 0.6.0-1
- Initial version
