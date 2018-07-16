#include <rte_eal.h>
#include <rte_lcore.h>
#include <rte_errno.h>
#include <rte_ethdev.h>
#include "dpdklib.h"
#include <rte_ethdev.h>
#include "logger.h"

nic_port nic_ports[MAX_NUMBER_OF_NIC_PORT];

uint8_t init_dpdk_capture(
    int argc,
    char** argv
)
{
    UNUSED( argc );
    int ret = rte_eal_init( 1, argv );
    if( ret < 0 ) {
        err( "Error while initializing EAL, error: \'%s\'",
             rte_strerror( rte_errno ) );
        return 0;
    }
    uint8_t nic_count = rte_eth_dev_count();
    log( "Discovered %d NIC ports.",
          nic_count );
    uint8_t nic = 0;
    for( nic = 0 ; nic < nic_count ; ++nic ) {
        collect_nic_port_data( nic );
    }
    return nic_count;
}

p_nic_port collect_nic_port_data( const uint8_t port_id )
{
    if( rte_eth_dev_is_valid_port( port_id ) == 0 ) {
        err( "NIC \'%"PRIu8"\' is not a valid port!", port_id );
        return NULL;
    }
    p_nic_port nic = &nic_ports[port_id];
    struct rte_eth_dev_info dev_info;

    rte_eth_dev_info_get( port_id, &dev_info );
    rte_eth_dev_get_name_by_port( port_id, nic->pci_dev_name );
    if( dev_info.if_index != 0 ) {
        if_indextoname( dev_info.if_index,
                        nic->if_name );
    }
    log( "Discovered NIC: PCI device name:\'%s\', driver name:\'%s\', if name:\'%s\'",
          nic->pci_dev_name,
          dev_info.driver_name,
          nic->if_name );
    return nic;
}

p_nic_port get_nic_data( const uint8_t port_id )
{
    if( port_id >= MAX_NUMBER_OF_NIC_PORT ) {
        return NULL;
    }
    return &nic_ports[port_id];
}
