// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/file_vector.h  (82 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/span.h"
#include "ocudu/support/error_handling.h"
#include <fstream>
#include <vector>


namespace ocudu {

/// \c file_vector open modes.

/// \c file_vector open modes.
enum class openmode {
  /// Opens the file in read-only mode.
  /// Opens the file in read-only mode.
  read_only,
  /// Opens the file in write-only mode.
  /// Opens the file in write-only mode.
  write_only,
  /// \brief Opens the file in read-write mode.
  ///
  /// Any previous content of the file will be lost.
  /// \brief Opens the file in read-write mode.
  ///
  /// Any previous content of the file will be lost.
  read_write
};

/// \brief Simple binary file input-output interface.
///
/// An object of this file allows reading and writing values of type \c T from and to a binary file.

/// \brief Simple binary file input-output interface.
///
/// An object of this file allows reading and writing values of type \c T from and to a binary file.
template <typename T>
class file_vector
{
  const char* file_name;
  openmode    op;


public:
  /// \brief Constructor.
  ///
  /// Sets the name and the mode (default is \e read-only) of the binary file. No operations are performed on the file.
  /// \brief Constructor.
  ///
  /// Sets the name and the mode (default is \e read-only) of the binary file. No operations are performed on the file.
  file_vector(const char* filename, openmode op_ = openmode::read_only) : file_name(filename), op(op_) {}

  /// Returns the file name.

  /// Returns the file name.
  const char* get_file_name() const { return file_name; }

  /// \brief Reads the file.
  ///
  /// The contents of the file are dumped to a \c std::vector<T>. The file is closed when the operation is completed.
  /// \warning An exception arises if the file cannot be opened or if the write-only open mode was specified at
  /// creation.

  /// \brief Reads the file.
  ///
  /// The contents of the file are dumped to a \c std::vector<T>. The file is closed when the operation is completed.
  /// \warning An exception arises if the file cannot be opened or if the write-only open mode was specified at
  /// creation.
  std::vector<T> read() const
  {
    report_fatal_error_if_not(op != openmode::write_only, "The file_vector was created with write-only permissions.");
    std::ifstream binary_file(file_name, std::ios::in | std::ios::binary);


    report_fatal_error_if_not(binary_file.is_open(), "Error opening file '{}'. {}.", file_name, ::strerror(errno));
    std::vector<T> read_data;


    T read_value;
    while (binary_file.read(reinterpret_cast<char*>(&read_value), sizeof(T))) {
      read_data.push_back(read_value);
    }


    return read_data;
  }

  /// \brief Writes data to the file.
  ///
  /// The sequence of \c T values viewed by \c write_data are written to the file.
  /// If the specified file does not exist, it is created. If it exists, previous contents will be erased.
  /// The file is closed when the operation is completed.
  ///
  /// \warning An exception arises if the file cannot be opened or if the read-only open mode was specified at creation.

  /// \brief Writes data to the file.
  ///
  /// The sequence of \c T values viewed by \c write_data are written to the file.
  /// If the specified file does not exist, it is created. If it exists, previous contents will be erased.
  /// The file is closed when the operation is completed.
  ///
  /// \warning An exception arises if the file cannot be opened or if the read-only open mode was specified at creation.
  void write(span<const T> write_data) const
  {
    report_fatal_error_if_not(op != openmode::read_only, "The file_vector was created with read-only permissions.");
    std::ofstream binary_file(file_name, std::ios::out | std::ios::binary);


    report_fatal_error_if_not(binary_file.is_open(), "Error opening file '{}'. {}.", file_name, ::strerror(errno));


    binary_file.write(reinterpret_cast<const char*>(write_data.begin()), write_data.size() * sizeof(T));
  }
};


} // namespace ocudu
