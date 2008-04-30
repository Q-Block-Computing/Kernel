#ifndef H_LOADER_NET
#define H_LOADER_NET

#include "loader.h"
#include <ip_addr.h>
#include <libdhcp.h>
#include <newt.h>
#include <pump.h>

#define DHCP_METHOD_STR   _("Dynamic IP configuration (DHCP)")
#define MANUAL_METHOD_STR _("Manual configuration")
#define AUTO_METHOD_STR   _("Automatic neighbor discovery (RFC 2461)")

/* generic names for array index positions in net.c */
enum { IPV4, IPV6 };

/* these match up to the radio button array index order in configureTCPIP() */
enum { IPV4_DHCP_METHOD, IPV4_MANUAL_METHOD };
enum { IPV6_AUTO_METHOD, IPV6_DHCP_METHOD, IPV6_MANUAL_METHOD };

struct networkDeviceConfig {
    struct pumpNetIntf dev;

    /* wireless settings */
    /* side effect: if this is non-NULL, then assume wireless */
    char * essid;
    char * wepkey;

    /* misc settings */
    int isDynamic;
    int noDns;
    int preset;
    int noipv4, noipv6, ipv4method, ipv6method;
    char * vendor_class;

    /* s390 settings */
    int mtu;
    char *subchannels, *portname, *peerid, *nettype, *ctcprot;
};

struct intfconfig_s {
    newtComponent ipv4Entry, cidr4Entry;
    newtComponent ipv6Entry, cidr6Entry;
    newtComponent gwEntry, nsEntry;
    const char *ipv4, *cidr4;
    const char *ipv6, *cidr6;
    const char *gw, *ns;
};

struct netconfopts {
    char ipv4Choice;
    char ipv6Choice;
};

typedef int int32;

int readNetConfig(char * device, struct networkDeviceConfig * dev,
                  char * dhcpclass, int methodNum);
int configureTCPIP(char * device, struct networkDeviceConfig * cfg,
                   struct networkDeviceConfig * newCfg,
                   struct netconfopts * opts, int methodNum);
int manualNetConfig(char * device, struct networkDeviceConfig * cfg,
                    struct networkDeviceConfig * newCfg,
                    struct intfconfig_s * ipcomps, struct netconfopts * opts);
void debugNetworkInfo(struct networkDeviceConfig *cfg);
int configureNetwork(struct networkDeviceConfig * dev);
int writeNetInfo(const char * fn, struct networkDeviceConfig * dev);
int findHostAndDomain(struct networkDeviceConfig * dev);
int writeResolvConf(struct networkDeviceConfig * net);
extern char *netServerPrompt;
int nfsGetSetup(char ** hostptr, char ** dirptr);
void initLoopback(void);
int chooseNetworkInterface(struct loaderData_s * loaderData);
void setupNetworkDeviceConfig(struct networkDeviceConfig * cfg, 
                              struct loaderData_s * loaderData);
int setupWireless(struct networkDeviceConfig *dev);

void setKickstartNetwork(struct loaderData_s * loaderData, int argc, 
                         char ** argv);

int kickstartNetworkUp(struct loaderData_s * loaderData,
                       struct networkDeviceConfig *netCfgPtr);

char *doDhcp(struct networkDeviceConfig *dev);
void netlogger(void *arg, int priority, char *fmt, va_list va);
void splitHostname (char *str, char **host, char **port);

#ifdef SDSC
int rocksNetworkUp(struct loaderData_s * loaderData,
	struct networkDeviceConfig *netCfgPtr);
#endif

#endif