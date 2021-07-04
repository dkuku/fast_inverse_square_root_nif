defmodule FISR.Nif do
  # When your move/rename this file (and you should) make sure
  # you also change the ERL_NIF_INIT call at the bottom of
  # c_src/#{name}_nif.c
  @on_load :init

  def init do
    path = :filename.join(:code.priv_dir(:fast_inv_sqr_nif), 'lib_fast_inverse_square_root')

    :ok = :erlang.load_nif(path, 1)
  end

  # A simple wrapper around the NIF call
  def fisr(float) do
    1 / :math.sqrt(float)
  end

  def fisrnif(float) do
    _fisr(float)
  end

  def fisr1(float) do
    _fisr1(float)
  end

  def fisr2(float) do
    _fisr2(float)
  end

  # This function will not be overwritten if the nif fails to load
  def _fisr(_) do
    exit(:nif_library_not_loaded)
  end

  def _fisr1(_) do
    exit(:nif_library_not_loaded)
  end

  def _fisr2(_) do
    exit(:nif_library_not_loaded)
  end
end
