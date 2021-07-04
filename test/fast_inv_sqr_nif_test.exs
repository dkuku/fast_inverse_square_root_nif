defmodule FastInvSqrNifTest do
  use ExUnit.Case
  doctest FastInvSqrNif

  test "greets the world" do
    assert FastInvSqrNif.hello() == :world
  end
end
