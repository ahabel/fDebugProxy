%define packer Andreas Habel <virus-d@fcms.de>

Name:           fcms-fdebug-proxy
Version:        0.1
Release:        1
Summary:        fDebug Proxy
Group:	        Utilities/System
License:        fpl
Vendor:		fCMS Development Team
Packager:	%packer
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-build
BuildRequires:  sqlite-devel
Source: 	fcms-fdebug-proxy.tar.gz
Provides:	fcms-fdebug-proxy-%version-%{release}

%description
fDebug Proxy Daemon

%prep
%setup -n %{name}

%build
cd release
make clean
make all

%install
[ ${RPM_BUILD_ROOT} != "/" ] && rm -rf ${RPM_BUILD_ROOT}
install -m 755 -d $RPM_BUILD_ROOT/usr/bin/
install -m 755 -d $RPM_BUILD_ROOT/var/log/fdebug/

# proxy binary
install -m 755 release/fdebug-proxy	$RPM_BUILD_ROOT/usr/bin/fdebug-proxy

# proxy scripts and config
install -m 755 -d			$RPM_BUILD_ROOT/var/lib/fdebug/
install -m 755 bin/fdebug-proxy 	$RPM_BUILD_ROOT/var/lib/fdebug/fdebug-proxy
install -m 644 bin/hostname		$RPM_BUILD_ROOT/var/lib/fdebug/hostname
install -m 644 bin/maxconnections	$RPM_BUILD_ROOT/var/lib/fdebug/maxconnections
install -m 644 bin/port			$RPM_BUILD_ROOT/var/lib/fdebug/port


%clean
[ ${RPM_BUILD_ROOT} != "/" ] && rm -rf ${RPM_BUILD_ROOT}

%files
%defattr(-,root,root,-)
/usr/bin/fdebug-proxy

/var/lib/fdebug/fdebug-proxy
/var/lib/fdebug/hostname
/var/lib/fdebug/maxconnections
/var/lib/fdebug/port

