// <copyright file="file-trace-listener.cpp" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

module;
#include <iostream>
#include <mutex>
#include <memory>
export module Opal:FileTraceListener;
import :TraceListener;
import :IOutputFile;

namespace Opal {
/// <summary>
/// File logger that wraps the base <see cref="TraceListener"/>
/// </summary>
export class FileTraceListener : public TraceListener {
private:
  std::mutex _mutex;
  std::shared_ptr<System::IOutputFile> _outputFile;

public:
  /// <summary>
  /// Initializes a new instance of the <see cref='FileTraceListener'/> class.
  /// </summary>
  FileTraceListener(std::shared_ptr<System::IOutputFile> outputFile)
      : TraceListener(), _mutex(), _outputFile(std::move(outputFile)) {}

  /// <summary>
  /// Initializes a new instance of the <see cref='FileTraceListener'/> class.
  /// </summary>
  FileTraceListener(std::shared_ptr<System::IOutputFile> outputFile,
                    std::string name, std::shared_ptr<IEventFilter> filter,
                    bool showEventType, bool showEventId, bool showTimestamp)
      : TraceListener(std::move(name), std::move(filter), showEventType,
                      showEventId, showTimestamp),
        _mutex(), _outputFile(std::move(outputFile)) {}

  /// <summary>
  /// Writes a message and newline terminator
  /// </summary>
  virtual void WriteLine(const std::string &message) override final {
    auto lock = std::lock_guard<std::mutex>(_mutex);
    _outputFile->GetOutStream() << message << std::endl;
  }
};
} // namespace Opal
