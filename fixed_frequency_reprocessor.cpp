#include "fixed_frequency_reprocessor.hpp"

FixedFrequencyReprocessor::FixedFrequencyReprocessor(int frequency, std::function<void(int, double, bool)> process_fun,
                                                     std::function<void(int)> re_fun)
    : process_fun(process_fun), reprocess_fun(re_fun), periodic_signal(frequency) {
    // Compute the period from frequency (time interval between each processing cycle)
    period = 1.0 / frequency;
}

bool FixedFrequencyReprocessor::attempt_to_process() {

    if (periodic_signal.process_and_get_signal()) {

        for (int id : ids_to_process) {
            double dt = periodic_signal.get_last_delta_time();
            id_to_delta_time[id] = dt;
            process_fun(id, dt, false);
            processed_ids.push_back(id);
        }
        ids_to_process.clear();
        return true;
    }
    return false;
}

void FixedFrequencyReprocessor::add_id(int id) {
    std::cout << "Adding ID: " << id << std::endl;
    ids_to_process.push_back(id);
}

void FixedFrequencyReprocessor::display_processed_ids() const {
    std::cout << "Processed IDs: ";
    for (const auto &id : processed_ids) {
        std::cout << id << " ";
    }
    std::cout << std::endl;
}

std::vector<int> FixedFrequencyReprocessor::get_ids_processed_after(int id) {
    std::vector<int> ids_after;
    for (const auto &processed_id : processed_ids) {
        if (processed_id > id) {
            ids_after.push_back(processed_id);
        }
    }
    return ids_after;
}

void FixedFrequencyReprocessor::re_process_after_id(int id) {
    std::cout << "Reprocessing activated after ID: " << id << std::endl;

    reprocess_fun(id);

    for (const auto &processed_id : processed_ids) {
        if (processed_id > id) {
            process_fun(processed_id, id_to_delta_time[processed_id], true);
        }
    }
    std::cout << "Reprocessing done" << std::endl;
}
