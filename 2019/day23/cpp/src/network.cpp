#include "network.hpp"

typedef std::vector<std::vector<int64_t>> vecvecint64_t;
typedef std::vector<int64_t> vecint64_t;

Network::Network(std::string file_name, int num_nodes)
    : m_file_name(file_name), m_num_nodes(num_nodes), m_nodes() {
  m_nodes = initialize_nodes();
}

std::vector<Intcode> Network::initialize_nodes() {
  std::vector<Intcode> nodes;

  for (auto i = 0; i < m_num_nodes; i++) {
    nodes.push_back(Intcode(m_file_name, {i}, false, false));
  }

  return nodes;
}

std::pair<int, int> Network::run() {
  // Keep track of inputs for each node
  vecvecint64_t inputs(m_num_nodes, vecint64_t());

  // Keep track of which node is sending what to where
  vecvecint64_t sending_to(m_num_nodes, vecint64_t());

  // Keep track of the NAT signal needed for part one and two
  vecint64_t NAT;
  int previous_nat_signal(-1), first_nat_signal(-1);

  // Keep going until nat signal triggers
  while (true) {
    // Place holder for sent input
    vecvecint64_t sent_input(m_num_nodes, vecint64_t());

    // Go through all nodes
    for (auto index = 0; index < m_num_nodes; index++) {
      // If idle, but has inputs in the buffer. Start it
      if (m_nodes[index].m_idle && inputs[index].size() > 0) {
        m_nodes[index].m_idle = false;
      }

      // If node is not idle run it with the inputs
      if (!m_nodes[index].m_idle) {
        auto output = m_nodes[index](inputs[index]);
        inputs[index].clear();

        if (std::get<1>(output) != -WINT_MAX) {
          m_nodes[index].m_idle = false;

          // Update where node is sending
          sending_to[index].push_back(std::get<1>(output));

          // If message lenght is 3 ( id, x,y) message is ready to be sent
          if (sending_to[index].size() == 3) {
            // 255 is NAT address
            if (sending_to[index][0] == 255) {
              NAT = vecint64_t({sending_to[index][1], sending_to[index][2]});
              if (first_nat_signal == -1) {
                first_nat_signal = NAT[1];
              }
              // Otherwise send to node
            } else {
              sent_input[sending_to[index][0]].push_back(sending_to[index][1]);
              sent_input[sending_to[index][0]].push_back(sending_to[index][2]);
            }

            // Clear the input
            sending_to[index].clear();
          }
        }
      }
    }
    // Update inputs
    inputs = sent_input;

    // Find how many nodes are idle
    int sm(0);
    for (auto &node_ : m_nodes) {
      sm += (node_.m_idle) ? 1 : 0;
    }

    // If all nodes are idle -> kickstart NAT
    if (sm == m_num_nodes) {
      if (NAT[1] == previous_nat_signal) {
        return std::make_pair(first_nat_signal, NAT[1]);
      } else {
        previous_nat_signal = NAT[1];
        inputs[0].push_back(NAT[0]);
        inputs[0].push_back(NAT[1]);
      }
    }
  }
}
