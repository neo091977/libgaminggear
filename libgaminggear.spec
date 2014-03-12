Name: libgaminggear
Version: 0.0.1
Release: 1
License: GPL
Source: %{name}-%{version}.tar.bz2
BuildRoot: %{_tmppath}/%{name}-%{version}-build
BuildRequires: cmake >= 2.6.4
BuildRequires: gtk2-devel >= 2.20
BuildRequires: libusb1-devel
ExclusiveOS: linux
Prefix: /usr
URL: ?
Packager: Stefan Achatz <erazor_de@users.sourceforge.net>

Summary: ?
Group: System Environment/Libraries

%package devel
Requires: libgaminggear
Summary: Development headers for libgaminggear.
Group: Development/Libraries

%description
?

%description devel
?
Here are the development headers needed to compile software that uses libgaminggear.

%prep
%setup -q -n %{name}-%{version}
%{__mkdir} build
cd build
cmake -DCMAKE_INSTALL_PREFIX="%{prefix}" ..

%build
cd build
%{__make} %{?_smp_mflags}

%install
cd build
%{__rm} -rf "%{buildroot}"
%{__make} %{?_smp_mflags} DESTDIR="%{buildroot}" install

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
%doc README COPYING Changelog
%{prefix}/lib*/gaminggear-*/libgaminggear.so*
%{prefix}/lib*/gaminggear-*/libgaminggearwidget.so*
%{prefix}/share/gaminggear
/etc/ld.so.conf.d/gaminggear-*.conf

%files devel
%defattr(-,root,root)
%{prefix}/include/gaminggear-*/gaminggear/*.h
%{prefix}/share/gaminggear/html
/usr/share/pkgconfig/gaminggear-*.pc
/usr/share/cmake/Modules/FindGAMINGGEAR*.cmake

%changelog
* Thu Feb 27 2014 Stefan Achatz <erazor_de@users.sourceforge.net> 0.0.1-1
- Initial version
