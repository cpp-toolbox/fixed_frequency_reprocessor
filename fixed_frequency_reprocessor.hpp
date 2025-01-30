#ifndef FIXED_FREQUENCY_REPROCESSOR_HPP
#define FIXED_FREQUENCY_REPROCESSOR_HPP

#include <vector>
#include <functional>
#include <iostream>
#include "../periodic_signal/periodic_signal.hpp"

/**
 * @brief A class for processing and reprocessing IDs at a fixed frequency.
 */
class FixedFrequencyReprocessor {
  private:
    std::vector<int> ids_to_process; ///< Vector of IDs that need to be processed.
    double period;                   ///< Time period (in seconds) between processing cycles, computed from frequency.
    std::unordered_map<int, double> id_to_delta_time;
    std::function<void(int, double, double)> process_fun; ///< Function to process each ID.
    std::function<void(int)> reprocess_fun;               ///< Function to reprocess IDs after a specific ID.
    PeriodicSignal periodic_signal;

  public:
    std::vector<int> processed_ids; ///< Vector of IDs that have been processed.
    /**
     * @brief Constructs a FixedFrequencyReprocessor.
     * @param frequency The number of times the process should happen per second.
     * @param fun Function to process each ID.
     * @param re_fun Function to reprocess IDs after a specific ID.
     */
    FixedFrequencyReprocessor(int frequency, std::function<void(int, double, bool)> process_fun,
                              std::function<void(int)> re_fun);

    /**
     * @brief Adds an ID to the list of IDs to be processed.
     * @param id The ID to add.
     */
    void add_id(int id);

    /**
     * @brief Attempts to process IDs if the accumulated time exceeds the processing interval.
     */
    bool attempt_to_process();

    /**
     * @brief Displays the list of processed IDs.
     */
    void display_processed_ids() const;

    /**
     * @brief Reprocesses IDs after a specified ID.
     * @param id The ID after which reprocessing starts.
     */
    void re_process_after_id(int id);

    std::vector<int> get_ids_processed_after(int id);
};

#endif // FIXED_FREQUENCY_REPROCESSOR_HPP
