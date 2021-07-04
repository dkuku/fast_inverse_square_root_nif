defmodule FastInvSqrNif do
  @moduledoc """
  Documentation for `FastInvSqrNif`.
  """

  @doc """
  Hello world.

  ## Examples

      iex> FastInvSqrNif.hello()
      :world

  """
  def calculate(float) do
    1/:math.sqrt(float)
  end
end
