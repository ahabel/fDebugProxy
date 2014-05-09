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
install -m 755 -d $RPM_BUILD_ROOT/var/log/fdebug/
install -m 755 -d $RPM_BUILD_ROOT/var/fdebug-proxy/
install -m 755 -d $RPM_BUILD_ROOT/var/fdebug-proxy/bin/


# proxy binary
install -m 755 release/fdebug-proxy	$RPM_BUILD_ROOT/var/fdebug-proxy/bin/fdebug-proxy

# proxy scripts and config
install -m 755 bin/run.sh		$RPM_BUILD_ROOT/var/fdebug-proxy/bin/run.sh
install -m 644 bin/hostname		$RPM_BUILD_ROOT/var/fdebug-proxy/hostname
install -m 644 bin/maxconnections	$RPM_BUILD_ROOT/var/fdebug-proxy/maxconnections
install -m 644 bin/port			$RPM_BUILD_ROOT/var/fdebug-proxy/port


%clean
[ ${RPM_BUILD_ROOT} != "/" ] && rm -rf ${RPM_BUILD_ROOT}

%files
%defattr(-,root,root,-)
/var/fdebug-proxy/bin/fdebug-proxy
/var/fdebug-proxy/bin/run.sh
/var/fdebug-proxy/hostname
/var/fdebug-proxy/maxconnections
/var/fdebug-proxy/port




