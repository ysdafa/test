#sbs-git:slp/apps/m/js_client js_client 0.1.0 27cb9ac9efc61361edf86770614768505e688a17
Name:       com.samsung.create_view
Summary:    create_view sample application
Version: 0.1.0
Release:    1
Group:      TO_BE/FILLED_IN
License:    Apache
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  pkgconfig(appcore-efl)
BuildRequires:  pkgconfig(appsvc)
BuildRequires:  pkgconfig(elementary)
BuildRequires:  pkgconfig(ecore)
BuildRequires:  pkgconfig(ecore-x)
BuildRequires:  pkgconfig(ecore-imf)
BuildRequires:  pkgconfig(ecore-input)
BuildRequires:  pkgconfig(appcore-common)
BuildRequires:  pkgconfig(bundle)
#BuildRequires:  pkgconfig(glib-2.0)
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
BuildRequires:  libjpeg-devel
#BuildRequires:  pkgconfig(capi-network-nfc)

BuildRequires:  cmake
BuildRequires:  edje-bin
BuildRequires:  embryo-bin
BuildRequires:  gettext-devel

%description
Map Sample application to test the Telmap service

%prep
%setup -q

%build
export PREFIX="/usr/apps/com.samsung.create_view"
export CFLAGS+=" -fPIC -g3 -O3"
export LDFLAGS+=" -Wl,--rpath=$(PREFIX)/lib -Wl,--as-needed -Wl,--hash-style=both"

cmake . -DCMAKE_INSTALL_PREFIX="$PREFIX"

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

%files
%manifest com.samsung.create_view.manifest
%defattr(-,root,root,-)
/usr/apps/com.samsung.create_view/*
/usr/share/applications/com.samsung.create_view.desktop
/usr/share/icons/default/small/com.samsung.create_view.png
/usr/share/packages/com.samsung.create_view.xml
%defattr(-,root,root,757)
/usr/apps/com.samsung.create_view/data/
