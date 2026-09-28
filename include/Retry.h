#pragma once

#include <exception>
#include <functional>
#include <optional>
#include <thread>
#include <chrono>

// Retry
template <typename Result, typename Exception = std::exception>
std::optional<Result> Retry(std::function<Result()> func, int retryCount, const std::chrono::milliseconds millisec, bool throwLast)
{
	int count = 0;
	while (count < retryCount + 1)
	{
		try
		{
			return func();
		}
		catch (const Exception&)
		{
			if (count == retryCount)
			{
				if (throwLast)
				{
					throw;
				}
				else
				{
					return std::nullopt;
				}
			}
			else
			{
				std::this_thread::sleep_for(millisec);
				++count;
			}
		}
	}

	return std::nullopt;
}

// Retry void
template <typename Exception = std::exception>
void RetryVoid(std::function<void()> func, int retryCount, const std::chrono::milliseconds millisec)
{
	int count = 0;
	while (count < retryCount + 1)
	{
		try
		{
			return func();
		}
		catch (const Exception&)
		{
			if (count == retryCount)
			{
				throw;
			}
			else
			{
				std::this_thread::sleep_for(millisec);
				++count;
			}
		}
	}
}