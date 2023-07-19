LICENSE = "CLOSED"

FILESEXTRAPATHS:append = "files"

FILES:${PN} += "/home/root"

S = "${WORKDIR}"

SRC_URI = " \
    file://Makefile \
    file://CException.cpp \
    file://CException.h \
    file://Conversions.h \
    file://CGeneralException.cpp \
    file://CGeneralException.h \
    file://CProductionTestException.cpp \
    file://CProductionTestException.h \
    file://EnTypes.h \
    file://IntelMgtTesterRegisterDefinitions.h \
    file://IRegisterInterface.h \
    file://LinuxIntelMgtTester.cpp \
    file://LinuxIntelMgtTester.h \
    file://LinuxRegisterInterface.cpp \
    file://LinuxRegisterInterface.h \
    file://main.cpp \
    file://Makefile \
    file://ProductionTestUtilTypes.h \
    file://RunnableTest.h \
    file://PackageHandler.h \
    file://PackageHandler.cpp \
    file://GenericPackageHandler.h \
    file://GenericPackage.h \
    file://MemoryMappedPackage.cpp \
    file://MemoryMappedPackage.h \
    file://AsyncPackage.cpp \
    file://AsyncPackage.h \
    file://ErrorPackage.cpp \
    file://ErrorPackage.h \
    file://PrintPackage.cpp \
    file://PrintPackage.h \
    file://ICommunicationInterface.h \
    file://IAsyncType.h \
    file://IObserver.h \
    file://Observer.cpp \
    file://Observer.h \
    file://Crc32.cpp \
    file://Crc32.h \
    file://LinuxComPort.cpp \
    file://LinuxComPort.h \
"

do_compile:append() {
    bbwarn "mgt test is recompiled"
}

do_install() {
    install -d ${D}/home/root
    install -m 0755 main ${D}/home/root
}
