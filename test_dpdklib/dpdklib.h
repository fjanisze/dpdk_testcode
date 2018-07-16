#include <unistd.h>
#include <inttypes.h>
#include <net/if.h>

#define UNUSED(x) (void)(x)
#define MAX_NUMBER_OF_NIC_PORT 64
#define MAX_PCI_DEVNAME        128

typedef struct nic_port_t {
    uint8_t                 port_id;
    char                    pci_dev_name[MAX_PCI_DEVNAME];
    char                    if_name[IF_NAMESIZE];
} nic_port, *p_nic_port;

p_nic_port collect_nic_port_data( const uint8_t port_id );
uint8_t    init_dpdk_capture(int argc,char** argv);
p_nic_port get_nic_data( const uint8_t port_id );
