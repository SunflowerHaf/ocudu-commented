// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/format/delimited_formatter.h  (238 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "fmt/format.h"


namespace ocudu {

/// \brief Format helper used to insert delimiters between structure fields.
///
/// This class is used to format the structures used by the channel processors. Its methods can be called from an \c fmt
/// custom formatter specialization to aid in format argument parsing and formatting of the structure fields. It
/// automatically inserts the chosen delimiter between the formatted fields.
/// \note The default delimiter is a space character, however, a new line delimiter can be selected by formatting with
/// the \c n format specifier, as in <tt>{:n}</tt>.
/// \note A short formatting mode can be selected by formatting with the \c s format specifier, as in <tt>{:s}</tt>.
/// This option can be used to exclude some of the structure fields for a more compact representation.

/// \brief Format helper used to insert delimiters between structure fields.
///
/// This class is used to format the structures used by the channel processors. Its methods can be called from an \c fmt
/// custom formatter specialization to aid in format argument parsing and formatting of the structure fields. It
/// automatically inserts the chosen delimiter between the formatted fields.
/// \note The default delimiter is a space character, however, a new line delimiter can be selected by formatting with
/// the \c n format specifier, as in <tt>{:n}</tt>.
/// \note A short formatting mode can be selected by formatting with the \c s format specifier, as in <tt>{:s}</tt>.
/// This option can be used to exclude some of the structure fields for a more compact representation.
class delimited_formatter
{
public:
  /// Default constructor.
  /// Default constructor.
  delimited_formatter()
  {
    static constexpr std::string_view DEFAULT_FORMAT    = "{}";
    static constexpr std::string_view DEFAULT_DELIMITER = " ";
    format_buffer.append(DEFAULT_FORMAT.begin(), DEFAULT_FORMAT.end());
    delimiter_buffer.append(DEFAULT_DELIMITER.begin(), DEFAULT_DELIMITER.end());
  }

  /// Constructor that sets the default delimiter according to the string \c default_delimiter.

  /// Constructor that sets the default delimiter according to the string \c default_delimiter.
  explicit delimited_formatter(std::string_view default_delimiter)
  {
    static constexpr std::string_view DEFAULT_FORMAT    = "{}";
    std::string_view                  DEFAULT_DELIMITER = default_delimiter;
    format_buffer.append(DEFAULT_FORMAT.begin(), DEFAULT_FORMAT.end());
    delimiter_buffer.append(DEFAULT_DELIMITER.begin(), DEFAULT_DELIMITER.end());
  }

  /// \brief Parsing helper for format specifiers.
  ///
  /// This helper detects the \c s and \c n short mode and new line delimiter specifiers. It also generates a format
  /// string with the parsed specifiers that can be used to propagate the formatting options to nested structures or
  /// structure fields.
  ///
  /// \tparam ParseContext Parse context type.
  /// \param[in] context A character range including the format specifiers.
  /// \return An iterator at the end of the parsed range.

  /// \brief Parsing helper for format specifiers.
  ///
  /// This helper detects the \c s and \c n short mode and new line delimiter specifiers. It also generates a format
  /// string with the parsed specifiers that can be used to propagate the formatting options to nested structures or
  /// structure fields.
  ///
  /// \tparam ParseContext Parse context type.
  /// \param[in] context A character range including the format specifiers.
  /// \return An iterator at the end of the parsed range.
  template <typename ParseContext>
  auto parse(ParseContext& context)
  {
    // Set the first field indicator.
    // Set the first field indicator.
    first = true;


    static constexpr std::string_view PREAMBLE_FORMAT     = "{:";
    static constexpr std::string_view NEWLINE_DELIMITER   = "\n  ";
    static constexpr std::string_view SEMICOLON_DELIMITER = "; ";

    // Skip if context is empty and use default format.

    // Skip if context is empty and use default format.
    if (context.begin() == context.end()) {
      return context.end();
    }


    format_buffer.clear();
    format_buffer.append(PREAMBLE_FORMAT.begin(), PREAMBLE_FORMAT.end());


    for (auto& it : context) {
      switch (it) {
        case 'n':
          // New line delimiter.
          // New line delimiter.
          delimiter_buffer.clear();
          delimiter_buffer.append(NEWLINE_DELIMITER.begin(), NEWLINE_DELIMITER.end());
          break;
        case ';':
          // Semicolon delimiter.
          // Semicolon delimiter.
          delimiter_buffer.clear();
          delimiter_buffer.append(SEMICOLON_DELIMITER.begin(), SEMICOLON_DELIMITER.end());
          break;
        case 's':
          // Short representation.
          // Short representation.
          verbose = false;
          break;
        case '}':
          format_buffer.push_back(it);
          return &it;
      }
      // Propagate formatting to underlying structures.
      // Propagate formatting to underlying structures.
      format_buffer.push_back(it);
    }
    // No end of context was found.
    // No end of context was found.
    return context.end();
  }

  /// \brief Formats one or more fields with the provided formatting options.
  ///
  /// Generates a string representation of the structure fields, according to the provided \c format formatting string,
  /// and writes it into the output iterator of the formatting \c context.
  ///
  /// \note The fields formatted with this method will be present in the default and the short form structure
  /// representations.
  ///
  /// \tparam FormatContext Format context type.
  /// \tparam Args Formatting arguments parameter pack.
  /// \param[in] context Formatting context, including an output iterator used to write the formatted representation.
  /// \param[in] format Formatting string, containing format specifiers.
  /// \param[in] args Fields to be formatted.

  /// \brief Formats one or more fields with the provided formatting options.
  ///
  /// Generates a string representation of the structure fields, according to the provided \c format formatting string,
  /// and writes it into the output iterator of the formatting \c context.
  ///
  /// \note The fields formatted with this method will be present in the default and the short form structure
  /// representations.
  ///
  /// \tparam FormatContext Format context type.
  /// \tparam Args Formatting arguments parameter pack.
  /// \param[in] context Formatting context, including an output iterator used to write the formatted representation.
  /// \param[in] format Formatting string, containing format specifiers.
  /// \param[in] args Fields to be formatted.
  template <typename FormatContext, typename... Args>
  void format_always(FormatContext& context, const char* format, Args&&... args) const
  {
    this->format_to(context, format, std::forward<Args>(args)...);
  }

  /// \brief Formats a single field or nested structure with the parsed formatting options.
  ///
  /// Generates a string representation of the structure field, according to the previously parsed formatting string,
  /// and writes it into the output iterator of the formatting \c context. It can be used to propagate the parsed
  /// formatting options to nested structures.
  ///
  /// \note The fields formatted with this method will be present in the default and the short form structure
  /// representations.
  ///
  /// \tparam FormatContext Format context type.
  /// \tparam Args Formatting arguments parameter pack.
  /// \param[in] context Formatting context, including an output iterator used to write the formatted representation.
  /// \param[in] args Fields to be formatted.

  /// \brief Formats a single field or nested structure with the parsed formatting options.
  ///
  /// Generates a string representation of the structure field, according to the previously parsed formatting string,
  /// and writes it into the output iterator of the formatting \c context. It can be used to propagate the parsed
  /// formatting options to nested structures.
  ///
  /// \note The fields formatted with this method will be present in the default and the short form structure
  /// representations.
  ///
  /// \tparam FormatContext Format context type.
  /// \tparam Args Formatting arguments parameter pack.
  /// \param[in] context Formatting context, including an output iterator used to write the formatted representation.
  /// \param[in] args Fields to be formatted.
  template <typename FormatContext, typename... Args>
  void format_always(FormatContext& context, Args&&... args) const
  {
    this->format_to(context, std::forward<Args>(args)...);
  }

  /// \brief Formats one or more fields with the provided formatting options.
  ///
  /// Generates a string representation of the structure fields, according to the provided \c format formatting string,
  /// and writes it into the output iterator of the formatting \c context.
  ///
  /// \note The fields formatted with this method will not be present in the short form structure representation.
  ///
  /// \tparam FormatContext Format context type.
  /// \tparam Args Formatting arguments parameter pack.
  /// \param[in] context Formatting context, including an output iterator used to write the formatted representation.
  /// \param[in] format Formatting string, containing format specifiers.
  /// \param[in] args Fields to be formatted.

  /// \brief Formats one or more fields with the provided formatting options.
  ///
  /// Generates a string representation of the structure fields, according to the provided \c format formatting string,
  /// and writes it into the output iterator of the formatting \c context.
  ///
  /// \note The fields formatted with this method will not be present in the short form structure representation.
  ///
  /// \tparam FormatContext Format context type.
  /// \tparam Args Formatting arguments parameter pack.
  /// \param[in] context Formatting context, including an output iterator used to write the formatted representation.
  /// \param[in] format Formatting string, containing format specifiers.
  /// \param[in] args Fields to be formatted.
  template <typename FormatContext, typename... Args>
  void format_if_verbose(FormatContext& context, const char* format, Args&&... args) const
  {
    if (verbose) {
      this->format_to(context, format, std::forward<Args>(args)...);
    }
  }

  /// \brief Formats a single field or nested structure with the parsed formatting options.
  ///
  /// Generates a string representation of the structure field, according to the previously parsed formatting string,
  /// and writes it into the output iterator of the formatting \c context. It can be used to propagate the parsed
  /// formatting options to nested structures.
  ///
  /// \note The fields formatted with this method will not be present in the short form structure representation.
  ///
  /// \tparam FormatContext Format context type.
  /// \tparam Args Formatting arguments parameter pack.
  /// \param[in] context Formatting context, including an output iterator used to write the formatted representation.
  /// \param[in] args Fields to be formatted.

  /// \brief Formats a single field or nested structure with the parsed formatting options.
  ///
  /// Generates a string representation of the structure field, according to the previously parsed formatting string,
  /// and writes it into the output iterator of the formatting \c context. It can be used to propagate the parsed
  /// formatting options to nested structures.
  ///
  /// \note The fields formatted with this method will not be present in the short form structure representation.
  ///
  /// \tparam FormatContext Format context type.
  /// \tparam Args Formatting arguments parameter pack.
  /// \param[in] context Formatting context, including an output iterator used to write the formatted representation.
  /// \param[in] args Fields to be formatted.
  template <typename FormatContext, typename... Args>
  void format_if_verbose(FormatContext& context, Args&&... args) const
  {
    if (verbose) {
      this->format_to(context, std::forward<Args>(args)...);
    }
  }
  /// \brief Returns \c true if the verbose representation is selected, \c false otherwise.
  /// \remark it must be called after \ref parse.
  /// \brief Returns \c true if the verbose representation is selected, \c false otherwise.
  /// \remark it must be called after \ref parse.
  bool is_verbose() const { return verbose; }


private:
  /// Internal method used to format with any formatting options.
  /// Internal method used to format with any formatting options.
  template <typename FormatContext, typename... Args>
  void format_to(FormatContext& context, const char* format, Args&&... args) const
  {
    if (!first) {
      // Buffer to hold the formatted string.
      // Buffer to hold the formatted string.
      fmt::memory_buffer temp_buffer;
      fmt::format_to(std::back_inserter(temp_buffer), format, std::forward<Args>(args)...);


      if (temp_buffer.size() > 0) {
        // Prepend delimiter to the formatted output.
        // Prepend delimiter to the formatted output.
        fmt::format_to(context.out(), "{}", std::string_view(delimiter_buffer.data(), delimiter_buffer.size()));
      }

      // Append the formatted string to the context iterator.

      // Append the formatted string to the context iterator.
      fmt::format_to(context.out(), "{}", std::string_view(temp_buffer.data(), temp_buffer.size()));


      return;
    }
    // Format without prepending delimiter.
    // Format without prepending delimiter.
    fmt::format_to(context.out(), format, std::forward<Args>(args)...);
    first = false;
  }

  /// Internal method used to format with the parsed formatting options.

  /// Internal method used to format with the parsed formatting options.
  template <typename FormatContext, typename... Args>
  void format_to(FormatContext& context, Args&&... args) const
  {
    if (!first) {
      // Buffer to hold the formatted string.
      // Buffer to hold the formatted string.
      fmt::memory_buffer temp_buffer;
      fmt::format_to(std::back_inserter(temp_buffer),
                     std::string_view(format_buffer.data(), format_buffer.size()),
                     std::forward<Args>(args)...);


      if (temp_buffer.size() > 0) {
        // Prepend delimiter to the formatted output.
        // Prepend delimiter to the formatted output.
        fmt::format_to(context.out(), "{}", std::string_view(delimiter_buffer.data(), delimiter_buffer.size()));
      }

      // Append the formatted string to the context iterator.

      // Append the formatted string to the context iterator.
      fmt::format_to(context.out(), "{}", std::string_view(temp_buffer.data(), temp_buffer.size()));


      return;
    }
    // Format without prepending delimiter.
    // Format without prepending delimiter.
    fmt::format_to(
        context.out(), std::string_view(format_buffer.data(), format_buffer.size()), std::forward<Args>(args)...);
    first = false;
  }

  /// First field flag. It is used to determine when to insert delimiters between fields.

  /// First field flag. It is used to determine when to insert delimiters between fields.
  mutable bool first = true;
  /// Verbose flag. Verbose format option includes all the fields of the structure in the formatted output.
  /// Verbose flag. Verbose format option includes all the fields of the structure in the formatted output.
  bool verbose = true;

  /// Delimiter string.

  /// Delimiter string.
  fmt::memory_buffer delimiter_buffer;
  /// Format string, used to propagate formatting options to nested structures.
  /// Format string, used to propagate formatting options to nested structures.
  fmt::memory_buffer format_buffer;
};


} // namespace ocudu
