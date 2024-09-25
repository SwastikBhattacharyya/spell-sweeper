#include "include/bloom_filter.h"
#include "include/murmur3.h"
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <vector>

size_t spell_sweeper::bloom_filter::get_size(uint32_t items_count,
                                             double fp_prob) {
  double num = items_count * std::log(fp_prob);
  double denum = std::pow(std::log(2), 2);

  return static_cast<size_t>(std::ceil(-num / denum));
}

void spell_sweeper::bloom_filter::init(uint32_t items_count, double fp_prob) {
  this->fp_prob = fp_prob;
  this->size = bloom_filter::get_size(items_count, fp_prob);
  this->hash_count = bloom_filter::get_hash_count(items_count, fp_prob);
  this->bitarray = std::vector<uint8_t>(size, 0);
}

uint32_t spell_sweeper::bloom_filter::get_hash_count(uint32_t items_count,
                                                     double fp_prob) {
  double num = bloom_filter::get_size(items_count, fp_prob) * std::log(2);
  double denum = items_count;

  return static_cast<uint32_t>(std::ceil(num / denum));
}

void spell_sweeper::bloom_filter::insert(std::string_view target) {
  for (uint32_t i = 0; i < this->hash_count; i++) {
    uint32_t digest;

    MurmurHash3_x86_32(target.data(), target.length(), i, &digest);
    digest %= this->size;

    this->bitarray[digest] = 1;
  }
}

bool spell_sweeper::bloom_filter::lookup(std::string_view target) {
  for (uint32_t i = 0; i < this->hash_count; i++) {
    uint32_t digest;

    MurmurHash3_x86_32(target.data(), target.length(), i, &digest);
    digest %= this->size;

    if (this->bitarray[digest] == 0)
      return false;
  }
  return true;
}

spell_sweeper::bloom_filter::bloom_filter(uint32_t items_count, double fp_prob)
    : fp_prob(fp_prob), size(bloom_filter::get_size(items_count, fp_prob)),
      hash_count(bloom_filter::get_hash_count(items_count, fp_prob)),
      bitarray(std::vector<uint8_t>(size, 0)) {}
