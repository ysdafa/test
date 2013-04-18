Name:		com.samsung.noa
Summary:	13' noa sample application
Version:	0.0.1
Release:	1
License:	To be filled
Summary:	13 NOA application
Packager:	Author SCR-Nanjing
Group:		Application
Source:		%{name}-%{version}.tar.gz

BuildRequires:  pkgconfig(appcore-efl)
BuildRequires:  pkgconfig(appsvc)
BuildRequires:  pkgconfig(elementary)
BuildRequires:  pkgconfig(ecore)
BuildRequires:  pkgconfig(ecore-x)
BuildRequires:  pkgconfig(ecore-imf)
BuildRequires:  pkgconfig(ecore-input)
BuildRequires:  pkgconfig(appcore-common)
BuildRequires:  pkgconfig(bundle)
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(utilX)
BuildRequires:  pkgconfig(eina)
BuildRequires:  pkgconfig(evas)
BuildRequires:  pkgconfig(edje)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(capi-appfw-application)
BuildRequires:  pkgconfig(capi-appfw-app-manager)
BuildRequires:  pkgconfig(capi-base-common)
#BuildRequires:  pkgconfig(capi-location-manager)
#BuildRequires:  pkgconfig(capi-location-geocoder)
#BuildRequires:  pkgconfig(capi-location-poi)
#BuildRequires:  pkgconfig(capi-location-route)
BuildRequires:  pkgconfig(ui-gadget-1)
#BuildRequires:  pkgconfig(capi-network-tethering)
#BuildRequires:  pkgconfig(wifi-direct)
#BuildRequires:  pkgconfig(cairo)
#BuildRequires:  pkgconfig(capi-network-nfc)
BuildRequires:  pkgconfig(alarm-service)
BuildRequires:  pkgconfig(alarm-engine)
BuildRequires:  pkgconfig(mm-player)
BuildRequires:  pkgconfig(mm-session)
BuildRequires:  pkgconfig(mm-sound)

BuildRequires:  libjpeg-devel
BuildRequires:	cmake
BuildRequires:	edje-bin
BuildRequires:	embryo-bin
BuildRequires:	gettext-devel

%description
Platform Project, porting 12NOA on Guggenheim platform to Tizen platform 

%prep
%setup -q

%define PREFIX    "/usr/apps/com.samsung.noa"

%build
#export LDFLAGS="${LDFLAGS} -Wl,--rpath,/usr/lib -Wl,--rpath,%{PREFIX}/lib -Wl,--hash-style=both -Wl,--as-needed"
export CFLAGS="${CFLAGS} -fPIC -g3 -O3"
export CXXFLAGS="${CXXFLAGS} -fPIC"

cmake . -DCMAKE_INSTALL_PREFIX=%{PREFIX}

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

%clean
make clean

%files
%manifest com.samsung.noa.manifest
%defattr(-,root,root,-)
/usr/apps/com.samsung.noa/*
/usr/apps/com.samsung.noa/lib/libnoa-common.so
/usr/apps/com.samsung.noa/lib/libnoa-common.so.0
/usr/apps/com.samsung.noa/lib/libnoa-common.so.0.1
/usr/share/applications/com.samsung.noa.desktop
/usr/share/icons/default/small/com.samsung.noa.png
/usr/share/packages/com.samsung.noa.xml
%defattr(-,root,root,757)
/usr/apps/com.samsung.noa/data/

%changelog
* Mon Apr 08 2013 Author suyan@samsung.com
 - initial release
