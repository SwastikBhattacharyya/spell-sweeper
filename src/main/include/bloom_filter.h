
#ifndef SPELL_SWEEPER_INCLUDE_BLOOM_FILTER_H
#define SPELL_SWEEPER_INCLUDE_BLOOM_FILTER_H

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <vector>

namespace spell_sweeper {
class bloom_filter {
public:
  double fp_prob;
  size_t size;
  uint32_t hash_count;
  std::vector<uint8_t> bitarray;

private:
  friend class boost::serialization::access;

  template <typename Archive>
  void serialize(Archive& archive, const unsigned int version) {
    archive& this->fp_prob;
    archive& this->size;
    archive& this->hash_count;
    archive& this->bitarray;
  }

public:
  bloom_filter() = default;
  bloom_filter(uint32_t items_count, double fp_prob);
  void init(uint32_t items_count, double fp_prob);
  void insert(std::string_view target);
  bool lookup(std::string_view target);

  static size_t get_size(uint32_t items_count, double fp_prob);
  static uint32_t get_hash_count(uint32_t items_count, double fp_prob);
};
} // namespace spell_sweeper

#endif
