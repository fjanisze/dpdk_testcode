extern "C" {
#include "../test_dpdklib/dpdklib.h"
}
#include <iostream>

int main( int argc, char** argv)
{
    int nic_count = init_dpdk_capture( argc, argv );
    std::cout<<"DPDK initialized, number of NICs "<<nic_count<<std::endl;
    for( int nic{0} ; nic < nic_count ; ++nic ){
        auto nic_data = get_nic_data(nic);
        std::cout<<"Found "<<nic_data->if_name <<" mapped to port "<<unsigned(nic_data->port_id)<<std::endl;
    }
    return 0;
}
